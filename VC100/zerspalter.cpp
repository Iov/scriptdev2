#include "precompiled.h"

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

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH,m_creature);
    }

    void JustReachedHome()
    {
        m_bIsPhase1 = true;
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

void AddSC_boss_zerspalter()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_zerspalter";
    pNewScript->GetAI = &GetAI_boss_zerspalter;
    pNewScript->RegisterSelf();
}