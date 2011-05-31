/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* Script Data Start
SDName: Boss Commander Stoutbeard
SD%Complete: ??%
SD author:FallenangelX
SDComment:  Only Horde Heroic
SDCategory:
Script Data End */

#include "precompiled.h"
#include "nexus.h"

enum
{
    SAY_AGGRO                                          = -1576024,   // need correct text
    SAY_KILL                                           = -1576025,   // need correct text
    SAY_DEATH                                          = -1576026,   // need correct text

    SPELL_BATTLE_SHOUT                                 = 31403,  // Increases the melee attack power of nearby friendly targets for 2 min.
    SPELL_CHARGE                                       = 60067,  // Charges an enemy, inflicting normal damage plus 75 and stuns the opponent for 2 sec.
    SPELL_FRIGHTENING_SHOUT                            = 19134,  // Shouts at nearby enemies causing them to flee in fear for 6 sec
    SPELL_WHIRLWIND_1                                  = 38618,  // triggers spell 38619 Attacks nearby enemies in a whirlwind of steel that lasts until cancelled. and inflicts double damage
    SPELL_WHIRLWIND_2                                  = 38619   // Attacks nearby enemies in a whirlwind of steel that inflicts 200% of weapon damage.
};

struct MANGOS_DLL_DECL boss_commander_stoutbeardAI : public ScriptedAI
{
    boss_commander_stoutbeardAI(Creature *pCreature) : ScriptedAI(pCreature) 
    {
        //m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        //m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    //ScriptedInstance* m_pInstance;
	//bool m_bIsRegularMode;

    uint32 SPELL_BATTLE_SHOUT_Timer;
    uint32 SPELL_CHARGE_Timer;
    uint32 SPELL_FRIGHTENING_SHOUT_Timer;
    uint32 SPELL_WHIRLWIND_1_Timer;
    uint32 SPELL_WHIRLWIND_2_Timer;

    void Reset() 
    {
        SPELL_BATTLE_SHOUT_Timer = 3000;   // needs adjusting
        SPELL_CHARGE_Timer = 2000;        // needs adjusting
        SPELL_FRIGHTENING_SHOUT_Timer = 2000;  // needs adjusting
        SPELL_WHIRLWIND_1_Timer = 0;   // THIS IS NOT RIGHT JUST A PLACEHOLDER FOR NOW
        SPELL_WHIRLWIND_2_Timer = 2000;   // needs adjusting


        //if (m_pInstance)
            //m_pInstance->SetData(TYPE_COMMANDER_STOUTBEARD, NOT_STARTED);
    }

    void EnterCombat(Unit* who)
    {
       /* DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COMMANDER_STOUTBEARD, IN_PROGRESS);*/
    }

    //void AttackStart(Unit* who) {}

    //void MoveInLineOfSight(Unit* who) {}
	
    void KilledUnit(Unit *victim)
    {
        //DoScriptText(SAY_KILL, m_creature);
    }
	
    void JustDied(Unit* killer)  
    {
        //DoScriptText(SAY_DEATH, m_creature);

        //if (m_pInstance)
            //m_pInstance->SetData(TYPE_COMMANDER_STOUTBEARD, DONE);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (SPELL_BATTLE_SHOUT_Timer < diff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BATTLE_SHOUT);
            SPELL_BATTLE_SHOUT_Timer = 3000 + rand()%5000;
        }else SPELL_BATTLE_SHOUT_Timer -= diff;

        if (SPELL_CHARGE_Timer < diff)  // this spell needs to be a distance check on victims in distance not a timer on victim
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CHARGE);
            SPELL_CHARGE_Timer = 2000 + rand()%5000;
        }else SPELL_CHARGE_Timer -= diff;

        if (SPELL_FRIGHTENING_SHOUT_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FRIGHTENING_SHOUT);
            SPELL_FRIGHTENING_SHOUT_Timer = 2000 + rand()%5000;
        }else SPELL_FRIGHTENING_SHOUT_Timer -= diff;

        if (SPELL_WHIRLWIND_2_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_WHIRLWIND_2);
            SPELL_WHIRLWIND_2_Timer = 2000 + rand()%5000;
        }else SPELL_WHIRLWIND_2_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_commander_stoutbeard(Creature* pCreature)
{
    return new boss_commander_stoutbeardAI (pCreature);
}

void AddSC_boss_commander_stoutbeard()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_commander_stoutbeard";
    newscript->GetAI = &GetAI_boss_commander_stoutbeard;
    newscript->RegisterSelf();
}
