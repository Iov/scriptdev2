#include "precompiled.h"
#include "sc_gossip.h"


#define GOSSIP_ITEM_ALLY "Wir sind fertig für den Kampf!"
#define GOSSIP_ITEM_HORDE "Wir sind bereit uns in die Schlacht zu stürzen!"

enum 
{
    QUEST_HORDE = 100003,
    QUEST_ALLY  = 100002,
    GOSSIP_TEXT_HORDE = 800001,
    GOSSIP_TEXT_ALLY  = 800000,
    SAY_HORDE_1 = -2000017,
    SAY_HORDE_2 = -2000018,
    SAY_HORDE_3 = -2000019,
    SAY_ALLY_1 = -2000020,
    SAY_ALLY_2 = -2000021,
    SAY_ALLY_3 = -2000022,
    NPC_ALLY   = 70015,
    NPC_HORDE  = 70016,
    NPC_BOSS   = 70010
};

struct MANGOS_DLL_DECL npc_eventhelperAI : public ScriptedAI
{
    npc_eventhelperAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiTimer;
    bool m_bGossipPossible;
    uint8 m_uiStep;
    bool m_bIsAlliance;
    ObjectGuid m_oPlayer;
    ObjectGuid m_oBoss;

    void Reset()
    {
        m_uiTimer = 500;
        m_bGossipPossible = true;
        m_uiStep = 4;
        m_oPlayer = NULL;
        m_bIsAlliance = m_creature->GetEntry() == NPC_ALLY;
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiStep < 4)
        {
                if (m_uiStep < 3)
                {
                    if (m_uiTimer < uiDiff)
                    {
                        switch(m_uiStep)
                        {
                            case 0: DoScriptText(m_bIsAlliance?SAY_ALLY_1:SAY_HORDE_1,m_creature); break;
                            case 1: DoScriptText(m_bIsAlliance?SAY_ALLY_2:SAY_HORDE_2,m_creature); break;
                            case 2: DoScriptText(m_bIsAlliance?SAY_ALLY_3:SAY_HORDE_3,m_creature); break;
                        }
                        ++m_uiStep;
                        m_uiTimer = 4500;
                    }
                } else if (m_uiStep == 3)
                {
                    if (Creature* pBoss = m_creature->GetClosestCreatureWithEntry(m_creature,NPC_BOSS,120.f))
                    {
                        m_oBoss = pBoss->GetObjectGuid();
                        pBoss->setFaction(14);
                        pBoss->SetVisibility(VISIBILITY_ON);
                        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_oPlayer))
                        {
                            pBoss->Attack(pPlayer, true);
                            pBoss->GetMotionMaster()->MoveChase(pPlayer);
                        }
                        else
                            pBoss->SetInCombatWithZone();
                    }
                    ++m_uiStep;
                }
            }
    }
};

bool GossipHello_npc_eventhelper(Player* pPlayer, Creature* pCreature)
{
    bool m_bGossipPossible = false;

    if (npc_eventhelperAI* pEventHelperAI = dynamic_cast<npc_eventhelperAI*>(pCreature->AI()))
    {
        m_bGossipPossible = pEventHelperAI->m_bGossipPossible;
    }

    if (!m_bGossipPossible)
        return true;

    if (pPlayer->HasQuest(QUEST_ALLY))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ALLY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXT_ALLY, pCreature->GetObjectGuid());
    }
    else if (pPlayer->HasQuest(QUEST_HORDE))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_HORDE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXT_HORDE, pCreature->GetObjectGuid());
    }

    return true;
}

bool GossipSelect_npc_eventhelper(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
   if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
   {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        if (npc_eventhelperAI* pEventHelperAI = dynamic_cast<npc_eventhelperAI*>(pCreature->AI()))
        {
            pEventHelperAI->m_oPlayer = pPlayer->GetObjectGuid();
            pEventHelperAI->m_bGossipPossible = false;
            pEventHelperAI->m_uiStep = 0;
        }
    }
    return true;
}

enum
{   
    SAY_FLAME_BREATH        = -2000000,
    SAY_TEMP_ENRAGE         = -2000016,
    SAY_AGGRO               = -2000001,
    SAY_ZURUECKSTOSSEN_1    = -2000002,
    SAY_ZURUECKSTOSSEN_2    = -2000010,
    SAY_RASEREI             = -2000003,
    SAY_ZERSCHMETTERN_1     = -2000004,
    SAY_ZERSCHMETTERN_2     = -2000011,
    SAY_ZERSCHMETTERN_3     = -2000012,
    SAY_ZERSCHMETTERN_4     = -2000013,
    SAY_PHASENWECHSEL       = -2000005,
    SAY_DEATH               = -2000006,
    SAY_SLAY_1              = -2000007,
    SAY_SLAY_2              = -2000008,
    SAY_SLAY_3              = -2000009,
    SAY_ADD_SPAWN           = -2000014,
    SAY_ADD_SPAWN_2         = -2000015,

    // Phase 1
    SPELL_ENRAGE            = 33232,
    SPELL_GROUND_SLAM       = 62625, // zurückstoßen
    SPELL_SLAM              = 67028, // zerschmettern
    SPELL_PETRIFY           = 11020, // versteinern
    SPELL_VIOLENT_EARTH     = 63149, // 
    SPELL_HEATED_GROUND     = 22202, //
    SPELL_GRAVITY_LAPSE     = 35941, // Beim Phasenwechsel
    NPC_ADD1                = 70011,

    // Phase 2
    SPELL_SHIELD_OF_DARKNESS= 67256,
    SPELL_BERSERK_TEMP_BERS = 64238, 
    SPELL_CHAIN_LIGHTNING   = 54531,
    SPELL_RAY_OF_SUFFERING  = 54417, 
    SPELL_FLAME_BREATH      = 17086, 
    SPELL_FUSE_LIGHTNING    = 64903, 
    SPELL_ARCANE_STORM      = 61694,
    NPC_ADD2                = 70012,
};

struct MANGOS_DLL_DECL boss_zerspalterAI : public ScriptedAI
{
    boss_zerspalterAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiEnrageTimer;
    uint32 m_uiAddSpawnTimer;
    uint32 m_uiGroundSlamTimer;
    uint32 m_uiSlamTimer;
    uint32 m_uiPetrifyTimer;
    uint32 m_uiViolentEarthTimer;
    uint32 m_uiHeatedGroundTimer;
    uint32 m_uiShieldOfDarknessTimer;
    uint32 m_uiTempBerserkTimer;
    bool m_bTempBerserkStop;
    uint32 m_uiChainLightningTimer;
    uint32 m_uiRayOfSufferingTimer;
    uint32 m_uiFlameBreathTimer;
    uint32 m_uiFuseLightningTimer;
    uint32 m_uiArcaneStormTimer;
    bool m_bIsPhase1;
    ObjectGuid m_oEventHelperGuid;

    void Reset()
    {
        m_uiEnrageTimer         = 600000; 
        m_uiAddSpawnTimer       = 5000; 
        m_uiGroundSlamTimer     = 15000; 
        m_uiSlamTimer           = 7000; 
        m_uiPetrifyTimer        = 10000; 
        m_uiViolentEarthTimer   = 8000; 
        m_uiHeatedGroundTimer   = 20000; 
        m_uiShieldOfDarknessTimer = 25000; 
        m_uiTempBerserkTimer    = 60000; 
        m_bTempBerserkStop      = false;
        m_uiChainLightningTimer = 3500; 
        m_uiRayOfSufferingTimer = 15000; 
        m_uiFlameBreathTimer    = 25000; 
        m_uiFuseLightningTimer  = 20000; 
        m_uiArcaneStormTimer    = 10000; 
        m_bIsPhase1 = true;
        m_oEventHelperGuid = NULL;

        m_creature->setFaction(35);
        m_creature->SetVisibility(VISIBILITY_OFF);

        if (m_oEventHelperGuid)
            if (Creature* pEventHelper = m_creature->GetMap()->GetCreature(m_oEventHelperGuid))
                if (npc_eventhelperAI* pEventHelperAI = dynamic_cast<npc_eventhelperAI*>(pEventHelper->AI()))
                {
                    pEventHelperAI->m_bGossipPossible = true;
                }
    }

    void Aggro()
    {
        DoScriptText(SAY_AGGRO,m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustRespawned()
    {
        if (Creature* pEventHelper = m_creature->GetMap()->GetCreature(m_oEventHelperGuid))
        {
            if (npc_eventhelperAI* pEventHelperAI = dynamic_cast<npc_eventhelperAI*>(pEventHelper->AI()))
            {
                pEventHelperAI->m_bGossipPossible = true;
            }
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH,m_creature);
    }

    void JustReachedHome()
    {
        m_bIsPhase1 = true;
        m_creature->setFaction(35);
        m_creature->SetVisibility(VISIBILITY_OFF);
        if (Creature* pEventHelper = m_creature->GetMap()->GetCreature(m_oEventHelperGuid))
        {
            if (npc_eventhelperAI* pEventHelperAI = dynamic_cast<npc_eventhelperAI*>(pEventHelper->AI()))
            {
                pEventHelperAI->m_bGossipPossible = true;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Enrage
        if (m_uiEnrageTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_ENRAGE, true);
            DoScriptText(SAY_RASEREI,m_creature);
            m_uiEnrageTimer = 60000;
        }
        else
            m_uiEnrageTimer -= uiDiff;

        // Add Spawn
        if (m_uiAddSpawnTimer < uiDiff)
        {
            DoScriptText(m_bIsPhase1?SAY_ADD_SPAWN:SAY_ADD_SPAWN_2,m_creature);
            m_creature->SummonCreature(m_bIsPhase1?NPC_ADD1:NPC_ADD2,m_creature->GetPositionX()+rand()%10,m_creature->GetPositionY()+rand()%10,m_creature->GetPositionZ(),0,TEMPSUMMON_CORPSE_DESPAWN,0);
            m_uiAddSpawnTimer = urand(8000,10000);
        }
        else
            m_uiAddSpawnTimer -= uiDiff;

        if (m_bIsPhase1) // Phase 1
        {
            if (m_creature->GetHealthPercent() == 50.f)
            {
                m_bIsPhase1 = false;
                DoScriptText(SAY_PHASENWECHSEL,m_creature);
                DoCast(m_creature,SPELL_GRAVITY_LAPSE, true);
            }

            // Ground Slam
            if (m_uiGroundSlamTimer < uiDiff)
            {
                switch(urand(0, 1))
                {
                    case 0: DoScriptText(SAY_ZURUECKSTOSSEN_1, m_creature); break;
                    case 1: DoScriptText(SAY_ZURUECKSTOSSEN_2, m_creature); break;
                }
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_GROUND_SLAM);
                m_uiGroundSlamTimer = urand(20000,40000);
            }
            else
                m_uiGroundSlamTimer -= uiDiff;

            // Slam
            if (m_uiSlamTimer < uiDiff)
            {
                switch(urand(0, 3))
                {
                    case 0: DoScriptText(SAY_ZERSCHMETTERN_1, m_creature); break;
                    case 1: DoScriptText(SAY_ZERSCHMETTERN_2, m_creature); break;
                    case 2: DoScriptText(SAY_ZERSCHMETTERN_3, m_creature); break;
                    case 3: DoScriptText(SAY_ZERSCHMETTERN_4, m_creature); break;
                }
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_SLAM);
                m_uiSlamTimer = urand(20000,25000);
            }
            else
                m_uiSlamTimer -= uiDiff;

            // Petrify
            if (m_uiPetrifyTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_PETRIFY);
                m_uiPetrifyTimer = urand(23000,29000);
            }
            else
                m_uiPetrifyTimer -= uiDiff;

            // Violent Earth
            if (m_uiViolentEarthTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCastSpellIfCan(pTarget, SPELL_VIOLENT_EARTH);
                m_uiViolentEarthTimer = urand(14000,18000);
            }
            else
                m_uiViolentEarthTimer -= uiDiff;

            // Heated Ground
            if (m_uiHeatedGroundTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCastSpellIfCan(pTarget, SPELL_HEATED_GROUND);
                m_uiHeatedGroundTimer = urand(6000,9000);
            }
            else
                m_uiHeatedGroundTimer -= uiDiff;

        }
        else // Phase 2
        {
            // Shield Of Darkness
            if (m_uiShieldOfDarknessTimer < uiDiff)
            {
                DoCast(m_creature,SPELL_SHIELD_OF_DARKNESS);
                m_uiShieldOfDarknessTimer = urand(35000,50000);
            }
            else
                m_uiShieldOfDarknessTimer -= uiDiff;

            // Temp Berserk
            if (m_uiTempBerserkTimer < uiDiff)
            {
                if (m_bTempBerserkStop)
                {
                    m_creature->RemoveAurasDueToSpell(SPELL_BERSERK_TEMP_BERS);
                    m_uiTempBerserkTimer = urand(35000,50000);
                }
                else
                {
                    DoScriptText(SAY_TEMP_ENRAGE,m_creature);
                    DoCast(m_creature,SPELL_BERSERK_TEMP_BERS);
                    m_uiTempBerserkTimer = 5000;
                }
            }
            else
                m_uiTempBerserkTimer -= uiDiff;
            
            // Chain Lightning
            if (m_uiChainLightningTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_CHAIN_LIGHTNING);
                m_uiChainLightningTimer = urand(8000,12000);
            }
            else
                m_uiChainLightningTimer -= uiDiff;

            // Ray Of Suffering
            if (m_uiRayOfSufferingTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_RAY_OF_SUFFERING);
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_RAY_OF_SUFFERING);
                m_uiRayOfSufferingTimer = urand(4000,20000);
            }
            else
                m_uiRayOfSufferingTimer -= uiDiff;

            // Flame Breath
            if (m_uiFlameBreathTimer < uiDiff)
            {
                DoScriptText(SAY_FLAME_BREATH, m_creature);
                DoCast(m_creature->getVictim(),SPELL_FLAME_BREATH);
                m_uiFlameBreathTimer = urand(15000,25000);
            }
            else
                m_uiFlameBreathTimer -= uiDiff;
            
            // Fuse Lightning
            if (m_uiFuseLightningTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_FUSE_LIGHTNING);
                m_uiFuseLightningTimer = urand(6000,25000);
            }
            else
                m_uiFuseLightningTimer -= uiDiff;

            // Arcane Storm
            if (m_uiArcaneStormTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_ARCANE_STORM);
                m_uiArcaneStormTimer = urand(2000,8000);
            }
            else
                m_uiArcaneStormTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_zerspalter(Creature* pCreature)
{
    return new boss_zerspalterAI(pCreature);
}

CreatureAI* GetAI_npc_eventhelper(Creature* pCreature)
{
    return new npc_eventhelperAI(pCreature);
}

void AddSC_boss_zerspalter()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_zerspalter";
    pNewScript->GetAI = &GetAI_boss_zerspalter;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_eventhelper";
    pNewScript->GetAI = &GetAI_npc_eventhelper;
    pNewScript->pGossipHello = &GossipHello_npc_eventhelper;
    pNewScript->pGossipSelect = &GossipSelect_npc_eventhelper;
    pNewScript->RegisterSelf();
}