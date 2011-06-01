/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_rotface
SD%Complete:
SDComment: by /dev/rsa, IOV
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum
{
    // Spells
    SPELL_OOZE_FLOOD                  = 69789,
    SPELL_OOZE_FLOOD_0                = 69788, // not used
    SPELL_OOZE_FLOOD_1                = 69783,
    SPELL_SLIME_SPRAY                 = 69508,
    SPELL_MUTATED_INFECTION_AURA      = 69674,
    SPELL_MUTATED_INFECTION           = 70003,
    SPELL_BERSERK                     = 47008,
    SPELL_STICKY_OOZE                 = 69774,
    SPELL_STICKY_AURA                 = 69776, // not used
    SPELL_MERGE_OOZE                  = 69889,
    SPELL_RADIATING_OOZE              = 69750,
    SPELL_RADIATING_OOZE_1            = 69760,
    SPELL_UNSTABLE_OOZE               = 69644,
    SPELL_UNSTABLE_OOZE_AURA          = 69558,
    SPELL_OOZE_EXPLODE                = 69839,
    SPELL_OOZE_EXPLODE_AURA           = 69840,

    // NPCs
    NPC_BIG_OOZE                      = 36899,
    NPC_SMALL_OOZE                    = 36897,
    NPC_STICKY_OOZE                   = 37006,
    NPC_OOZE_SPRAY_STALKER            = 37986,
    NPC_OOZE_STALKER                  = 37013,
    NPC_OOZE_EXPLODE_STALKER          = 38107,

    // Texts
    SAY_AGGRO                         = -1631221,
    SAY_KILL1                         = -1631222,
    SAY_KILL2                         = -1631223,
    SAY_DEATH                         = -1631224,
    SAY_ENRAGE                        = -1631225,
    SAY_INFECTION                     = -1631226,
    SAY_OOZE                          = -1631227,
    SAY_PRECIOUS_DEATH                = -1631228,

    // Achievements
};

static Locations SpawnLoc[]=
{
    {4471.821289f, 3162.986084f, 360.38501f},  // 0
    {4471.821289f, 3110.452148f, 360.38501f},  // 1
    {4418.825684f, 3110.452148f, 360.38501f},  // 2
    {4418.825684f, 3162.986084f, 360.38501f},  // 3
};

struct MANGOS_DLL_DECL boss_rotfaceAI : public ScriptedAI
{
    boss_rotfaceAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMode = pCreature->GetMap()->GetDifficulty();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    uint8 m_uiMode;

    bool m_bIntro;
    bool m_bPet;
    bool m_bNextTick;
    uint8 m_uiMutatedInfactionCount;
    uint32 m_uiEnrageTimer;
    uint32 m_uiMutatedInfactionTimer;
    uint32 m_uiSlimeSprayTimer;
    uint32 m_uiOozeFloodTimer;
    Unit* pOozeStalker;

    void Reset()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ROTFACE, NOT_STARTED);

        m_bIntro = false;
        m_bPet = false;
        m_bNextTick = false;
        m_uiMutatedInfactionCount = 0;
        m_uiEnrageTimer = 10*MINUTE*IN_MILLISECONDS;
        m_uiMutatedInfactionTimer = 14*IN_MILLISECONDS;
        m_uiSlimeSprayTimer = 15*IN_MILLISECONDS;
        m_uiOozeFloodTimer = 25*IN_MILLISECONDS;
        pOozeStalker = NULL;
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (m_bIntro)
            return;

        if (pWho->GetTypeId() != TYPEID_PLAYER)
            return;

        // used for event with Professor Putricide
        m_pInstance->SetData(TYPE_EVENT, 600);
        debug_log("EventMGR: creature %u send signal %u ",m_creature->GetEntry(),m_pInstance->GetData(TYPE_EVENT));

        m_bIntro = true;
    }

    void KilledUnit(Unit* pVictim)
    {
        switch (urand(0,1))
        {
            case 0:
               DoScriptText(SAY_KILL1, m_creature, pVictim);
               break;
            case 1:
               DoScriptText(SAY_KILL2, m_creature, pVictim);
               break;
        }
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ROTFACE, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature, pWho);
    }

    void JustDied(Unit *pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ROTFACE, DONE);

        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {

        if(!m_pInstance)
            return;

        if (!m_bPet)
        {
            if (Creature* pGuard = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_PRECIOUS)))
                if (!pGuard->isAlive())
                {
                     m_bPet = true;
                     if (m_pInstance->GetData(TYPE_PRECIOUS) == NOT_STARTED)
                     {
                         DoScriptText(SAY_PRECIOUS_DEATH, m_creature);
                         m_pInstance->SetData(TYPE_PRECIOUS,DONE);
                     }
                }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bNextTick)
        {
            if (pOozeStalker)
            {
                pOozeStalker->CastSpell(pOozeStalker, SPELL_OOZE_FLOOD_1, false);
                pOozeStalker = NULL;
            }

            DoScriptText(SAY_OOZE, m_creature);
            m_bNextTick = false;
        }

        if (m_uiOozeFloodTimer < uiDiff)
        {
            uint8 i = urand(0,3);

            if (pOozeStalker = m_creature->SummonCreature(NPC_OOZE_STALKER, SpawnLoc[i].x, SpawnLoc[i].y, SpawnLoc[i].z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 15000))
            {
                pOozeStalker->CastSpell(pOozeStalker, SPELL_OOZE_FLOOD, false);
                m_bNextTick = true;
            }

            m_uiOozeFloodTimer = 20*IN_MILLISECONDS;
        }
        else
            m_uiOozeFloodTimer -= uiDiff;

        if (m_uiSlimeSprayTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (Unit* pSpellTarget = m_creature->SummonCreature(NPC_OOZE_SPRAY_STALKER, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10000))
                    DoCast(pSpellTarget, SPELL_SLIME_SPRAY);

            m_uiSlimeSprayTimer = 21.5*IN_MILLISECONDS;
        }
        else
            m_uiSlimeSprayTimer -= uiDiff;

        if (m_uiMutatedInfactionTimer < uiDiff)
        {
            if (!m_creature->IsNonMeleeSpellCasted(false))
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    if (!pTarget->HasAura(SPELL_MUTATED_INFECTION_AURA))
                    {
                        DoCast(pTarget, SPELL_MUTATED_INFECTION);
                        DoScriptText(SAY_INFECTION, m_creature);

                        switch (m_uiMutatedInfactionCount)
                        {
                            case 0: case 1: case 2: case 3:
                                m_uiMutatedInfactionTimer = 14*IN_MILLISECONDS;
                                break;
                            case 4: case 5: case 6: case 7:
                                m_uiMutatedInfactionTimer = 12*IN_MILLISECONDS;
                                break;
                            case 8: case 9: case 10: case 11:
                                m_uiMutatedInfactionTimer = 10*IN_MILLISECONDS;
                                break;
                            case 12: case 13: case 14: case 15:
                                m_uiMutatedInfactionTimer = 8*IN_MILLISECONDS;
                                break;
                            default:
                                m_uiMutatedInfactionTimer = 6*IN_MILLISECONDS;
                                break;
                        }

                        m_uiMutatedInfactionCount++;
                    }
        }
        else
            m_uiMutatedInfactionTimer -= uiDiff;

        if (m_uiEnrageTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_BERSERK);
            DoScriptText(SAY_ENRAGE, m_creature);

            m_uiEnrageTimer = 10*MINUTE*IN_MILLISECONDS;
        }
        else
            m_uiEnrageTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_rotface(Creature* pCreature)
{
    return new boss_rotfaceAI(pCreature);
}

struct MANGOS_DLL_DECL mob_small_oozeAI : public ScriptedAI
{
    mob_small_oozeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiStickyOozeTimer;

    void Reset()
    {
        DoCast(m_creature, SPELL_RADIATING_OOZE);
        m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
        m_creature->SetSpeedRate(MOVE_RUN, 0.5);
        m_creature->SetSpeedRate(MOVE_WALK, 0.5);

        m_uiStickyOozeTimer = 5*IN_MILLISECONDS;
   }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStickyOozeTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_STICKY_OOZE);

            m_uiStickyOozeTimer = 15*IN_MILLISECONDS;
        }
        else
            m_uiStickyOozeTimer -= uiDiff;

        if (Creature* pTemp = GetClosestCreatureWithEntry(m_creature, NPC_SMALL_OOZE, 7.0f))
        {
            DoCast(pTemp, SPELL_MERGE_OOZE);
            m_creature->SummonCreature(NPC_BIG_OOZE, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 10000);
            pTemp->ForcedDespawn();
            m_creature->ForcedDespawn();
        }
    }
};

CreatureAI* GetAI_mob_small_ooze(Creature* pCreature)
{
    return new mob_small_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_big_oozeAI : public ScriptedAI
{
    mob_big_oozeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiStickyOozeTimer;

    void Reset()
    {
        DoCast(m_creature, SPELL_UNSTABLE_OOZE);
        m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
        m_creature->SetSpeedRate(MOVE_RUN, 0.5);
        m_creature->SetSpeedRate(MOVE_WALK, 0.5);

        m_uiStickyOozeTimer = 5*IN_MILLISECONDS;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->HasAura(SPELL_UNSTABLE_OOZE_AURA))
        {
            if (m_creature->GetAura(SPELL_UNSTABLE_OOZE_AURA, EFFECT_INDEX_0)->GetStackAmount() > 4)
                DoCast(m_creature, SPELL_OOZE_EXPLODE);
        }

        if (m_uiStickyOozeTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_STICKY_OOZE);

            m_uiStickyOozeTimer = 15*IN_MILLISECONDS;
        }
        else
            m_uiStickyOozeTimer -= uiDiff;

        if (Creature* pSmall = GetClosestCreatureWithEntry(m_creature, NPC_SMALL_OOZE, 5.0f))
        {
            pSmall->ForcedDespawn();
            DoCast(m_creature, SPELL_UNSTABLE_OOZE);
        }

        if (Creature* pBig = GetClosestCreatureWithEntry(m_creature, NPC_BIG_OOZE, 8.0f))
        {
            pBig->ForcedDespawn();
            DoCast(m_creature, SPELL_UNSTABLE_OOZE);
        }
    }
};

CreatureAI* GetAI_mob_big_ooze(Creature* pCreature)
{
    return new mob_big_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_sticky_oozeAI : public ScriptedAI
{
    mob_sticky_oozeAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;

    void Reset()
    {
        m_creature->SetDisplayId(11686);
        m_creature->CastSpell(m_creature, SPELL_STICKY_AURA, true);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetInCombatWithZone();
        SetCombatMovement(false);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_sticky_ooze(Creature* pCreature)
{
    return new mob_sticky_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_ooze_explode_stalkerAI : public BSWScriptedAI
{
    mob_ooze_explode_stalkerAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    Creature* pCreator;
    uint32 m_uiOozeExplodeTimer;

    void Reset()
    {
        m_creature->SetDisplayId(11686);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        SetCombatMovement(false);
        m_creature->SetInCombatWithZone();
        DoCast(m_creature, SPELL_OOZE_EXPLODE_AURA);
        pCreator = GetClosestCreatureWithEntry(m_creature, NPC_BIG_OOZE, 20.0f);

        m_uiOozeExplodeTimer = 2*IN_MILLISECONDS;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (pCreator && pCreator->isAlive())
            pCreator->ForcedDespawn();

        if (m_uiOozeExplodeTimer < uiDiff)
            m_creature->ForcedDespawn();
        else
            m_uiOozeExplodeTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_ooze_explode_stalker(Creature* pCreature)
{
    return new mob_ooze_explode_stalkerAI(pCreature);
}

struct MANGOS_DLL_DECL mob_ooze_spray_stalkerAI : public ScriptedAI
{
    mob_ooze_spray_stalkerAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        SetCombatMovement(false);
        m_creature->SetInCombatWithZone();
        m_creature->SetDisplayId(11686);
    }

    void AttackStart(Unit *pWho)
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_ROTFACE) != IN_PROGRESS)
            m_creature->ForcedDespawn();
    }
};

CreatureAI* GetAI_mob_ooze_spray_stalker(Creature* pCreature)
{
    return new mob_ooze_spray_stalkerAI(pCreature);
}

void AddSC_boss_rotface()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_rotface";
    pNewScript->GetAI = &GetAI_boss_rotface;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_small_ooze";
    pNewScript->GetAI = &GetAI_mob_small_ooze;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_big_ooze";
    pNewScript->GetAI = &GetAI_mob_big_ooze;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_sticky_ooze";
    pNewScript->GetAI = &GetAI_mob_sticky_ooze;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_ooze_explode_stalker";
    pNewScript->GetAI = &GetAI_mob_ooze_explode_stalker;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_ooze_spray_stalker";
    pNewScript->GetAI = &GetAI_mob_ooze_spray_stalker;
    pNewScript->RegisterSelf();
}
