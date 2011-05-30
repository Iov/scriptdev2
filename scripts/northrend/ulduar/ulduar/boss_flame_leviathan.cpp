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
SDName: boss_leviathan
SD%Complete: 
SDComment: probably still many bugs, achievements not implemented, vehicles on leviathan needs support, speech not fully implemented
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"
#include "Vehicle.h"

enum say
{
    SAY_AGGRO           = -1603203,
    SAY_DEATH           = -1603202,
    SAY_SLAY            = -1603201,
    SAY_CHANGE1         = -1603204,
    SAY_CHANGE2         = -1603205,
    SAY_CHANGE3         = -1603206,
    SAY_PLAYER_ON_TOP   = -1603207,
    SAY_OVERLOAD1       = -1603208,
    SAY_OVERLOAD2       = -1603209,
    SAY_OVERLOAD3       = -1603210,
    SAY_HARD_MODE       = -1603211,
    SAY_TOWERS_DOWN     = -1603212,
    SAY_FROST_TOWER     = -1603213,
    SAY_FIRE_TOWER      = -1603214,
    SAY_ENERGY_TOWER    = -1603215,
    SAY_NATURE_TOWER    = -1603216,

    EMOTE_PURSUE        = -1603352,
};

enum spells
{
    // leviathan
    SPELL_PURSUED           = 62374,

    SPELL_MISSILE_BARRAGE   = 62400,
    SPELL_FLAME_VENTS       = 62396,
    SPELL_BATTERING_RAM     = 62376,

    SPELL_GATHERING_SPEED   = 62375,
    // interupted by
    SPELL_OVERLOAD_CIRCUIT  = 62399,

    SPELL_SEARING_FLAME     = 62402, // used by defense turret
    // interupted by
    SPELL_SYSTEMS_SHUTDOWN  = 62475,

    SPELL_FLAME_CANNON      = 62395,
    //SPELL_FLAME_CANNON    = 64692, trigger the same spell
    SPELL_BLAZE             = 62292,

    // used by players -> to be added later
    SPELL_ELECTROSHOCK      = 62522,
    SPELL_SMOKE_TRAIL       = 63575,

    // tower of life
    SPELL_FREYAS_WARD_MISSILE   = 62906,
    SPELL_SUMMON_LASHER         = 62947,
    SPELL_SUMMON_WARD           = 62907,
    SPELL_TOWER_OF_LIFE         = 64482,
    // tower of flames
    SPELL_MIMIRON_INFERNO       = 62910, // summons fire-pit
    SPELL_MIMIRON_INF_MISSILE   = 62909,
    SPELL_TOWER_OF_FLAMES_BUFF  = 65075,
    // tower of frost
    SPELL_TOWER_OF_FROST_BUFF   = 65077,
    SPELL_TOWER_OF_FROST_DEBUFF = 65079,
    SPELL_HODIRS_FURY_MISSILE   = 62533,
    SPELL_HODIR_FURY            = 62297, // freezes target in iceblock
    // tower of storms
    SPELL_THORIMS_HAMMER        = 62912, // area damage
    SPELL_THORIMS_HAMMER_MISSILE= 62911,
    SPELL_TOWER_OF_STORMS       = 65076,

    // repair station
    SPELL_AUTO_REPAIR           = 62705,

    // hardmode mob spells
    AURA_DUMMY_BLUE             = 63294,
    AURA_DUMMY_GREEN            = 63295,
    AURA_DUMMY_YELLOW           = 63292,

    //mechanolift
    SPELL_LIQUID_PYRITE         = 62494,
};

enum Mobs
{
    MOB_MECHANOLIFT     = 33214,
    MOB_LIQUID          = 33189,
    MOB_CONTAINER       = 33218,

    DEFENSE_TURRET      = 33142,
    KEEPER_OF_NORGANNON = 33686,

    MOB_THORIM_BEACON               = 33365,
    MOB_MIMIRON_BEACON              = 33370,
    MOB_HODIR_BEACON                = 33212,
    MOB_FREYA_BEACON                = 33367,
    NPC_THORIM_TARGET_BEACON        = 33364,
    NPC_MIMIRON_TARGET_BEACON       = 33369,
    NPC_HODIR_TARGET_BEACON         = 33108,
    NPC_FREYA_TARGET_BEACON         = 33366, // I use this as mob for mimirons_inferno script, because MOB_MIMIRON_BEACON is already used in boss_mimiron script :-S 
    NPC_LOREKEEPER                  = 33686, //Hard mode starter
    NPC_BRANZ_BRONZBEARD            = 33579,
    NPC_DELORAH                     = 33701,
    NPC_ULDUAR_GAUNTLET_GENERATOR   = 33571, // Trigger tied to towers
    NPC_STEELFORGE_DEFENDER         = 33236, // summoned by gauntlet generators

    // towers
    GO_STORM_BEACON_1   =	194412,
    GO_STORM_BEACON_2   =	194415,
    GO_STORM_BEACON_3   =	194405,
    GO_STORM_BEACON_4   =	194404,
    GO_STORM_BEACON_5   =	194402,
    GO_STORM_BEACON_6   =	194506,
    GO_STORM_BEACON_7   =	194403,
    GO_STORM_BEACON_8   =	194406,
    GO_STORM_BEACON_9   =	194407,
    GO_STORM_BEACON_10  =	194408,
    GO_STORM_BEACON_11  =	194409,
    GO_STORM_BEACON_12  =	194410,
    GO_STORM_BEACON_13  =	194413,
    GO_STORM_BEACON_14  =	194414,
    GO_STORM_BEACON_15  =	194401,
    GO_STORM_BEACON_16  =	194411,
    GO_STORM_BEACON_17  =	194400,
    GO_STORM_BEACON_18  =	194398,
    GO_STORM_BEACON_19  =	194399,
};

enum Seats
{
    SEAT_PLAYER = 0,
    SEAT_TURRET = 1,
    SEAT_DEVICE = 2,
};

enum Achievements
{
    ACHIEV_10_NUKED_FROM_ORBIT                  = 2915,
    ACHIEV_25_NUKED_FROM_ORBIT                  = 2917,
    ACHIEV_10_ORBITAL_BOMBARDMENT               = 2913,
    ACHIEV_25_ORBITAL_BOMBARDMENT               = 2918,
    ACHIEV_10_ORBITAL_DEVASTATION               = 2914,
    ACHIEV_25_ORBITAL_DEVASTATION               = 2916,
    ACHIEV_10_ORBIT_UARY                        = 3056,
    ACHIEV_25_ORBIT_UARY                        = 3057,
    ACHIEV_10_SHUTOUT                           = 2911,
    ACHIEV_25_SHUTOUT                           = 2912,
    ACHIEV_10_SIEGE_OF_ULDUAR                   = 2886,
    ACHIEV_25_SIEGE_OF_ULDUAR                   = 2887,
    ACHIEV_10_THREE_CAR_GARAGE                  = 2907, 
    ACHIEV_25_THREE_CAR_GARAGE                  = 2908, 
    ACHIEV_10_UNBROKEN                          = 2905,
    ACHIEV_25_UNBROKEN                          = 2906,
};

struct Locations
{
    float posX;
    float posY;
    float posZ;
    int id;
};

static Locations mimironInfernoPositions[4] = 
{
    {390.93f, -13.91f, 409.81f,0},
    {290.30f, 69.36f, 410.60f,1},
    {154.25f, -32.97f, 409.80f,2},
    {241.88f, -141.73f, 409.58f,3}
};

static Locations freyaPositions[4] =
{
    {377.02f, -119.10f, 409.81f,0},
    {377.02f, 54.78f, 409.81f,0},
    {185.62f, 54.78f, 409.81f,0},
    {185.62f, -119.10f, 409.81f,0}
};

struct MANGOS_DLL_DECL boss_flame_leviathan : public ScriptedAI
{
    boss_flame_leviathan(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiBatteringRamTimer;
    uint32 m_uiFlameVentsTimer;
    uint32 m_uiMissileBarrageTimer;
    uint32 m_uiPursueTimer;
    uint32 m_uiGatheringSpeedTimer;
    uint32 m_uiSummonMechanoliftTimer;
    uint8 m_uiMechanoliftCount;

    bool m_bIsHardMode;
    bool m_bIsHodirsTower;
    bool m_bIsFreyasTower;
    bool m_bIsMimironsTower;
    bool m_bIsThorimsTower;

    void Reset()
    {
        m_uiBatteringRamTimer   = 15000 + rand()%20000;
        m_uiFlameVentsTimer     = 15000 + rand()%10000;
        m_uiMissileBarrageTimer = 1000;
        m_uiPursueTimer         = 30000;
        m_uiGatheringSpeedTimer = 50000;
        m_uiSummonMechanoliftTimer    = 2000;
        m_uiMechanoliftCount    = 10;

        m_bIsHardMode      = false;
        m_bIsHodirsTower   = false;
        m_bIsFreyasTower   = false;
        m_bIsMimironsTower = false;
        m_bIsThorimsTower  = false;

        m_creature->SetSpeedRate(MOVE_RUN, 0.3f);
    }

    void Aggro(Unit *who) 
    {
        if(m_pInstance) 
        {
            m_pInstance->SetData(TYPE_LEVIATHAN, IN_PROGRESS);
            if(m_pInstance->GetData(TYPE_LEVIATHAN_TP) != DONE)
                m_pInstance->SetData(TYPE_LEVIATHAN_TP, DONE);

            if (m_pInstance->GetData(TYPE_LEVIATHAN_HARD) == IN_PROGRESS)
            {
                m_bIsHardMode = true;
                GameObject* pTower;
                if (pTower = m_creature->GetMap()->GetGameObject(m_pInstance->GetData64(GO_TOWER_OF_FROST)))
                    if (pTower->HasFlag(GAMEOBJECT_FLAGS,GO_FLAG_DESTROYED))
                    {
                        m_creature->CastSpell(m_creature, SPELL_TOWER_OF_FROST_BUFF, true);

                        Map::PlayerList const& pPlayers = m_creature->GetMap()->GetPlayers();
                        Player *pPlayer;
                        if (!pPlayers.isEmpty())
                           for (Map::PlayerList::const_iterator itr = pPlayers.begin(); itr != pPlayers.end(); ++itr)
                           {
                               if (pPlayer = itr->getSource())
                                   if (pPlayer->isAlive() && !pPlayer->isGameMaster())
                                       m_creature->CastSpell(pPlayer, SPELL_TOWER_OF_FROST_DEBUFF, true);
                           }

                        m_bIsHodirsTower = true;

                        float x,y,z;
                        for (uint8 i = 0; i < 7; ++i)
                        {
                            GetRandomPoint(x,y,z,urand(0,50));
                            if (Creature* pHodir = m_creature->SummonCreature(MOB_HODIR_BEACON,x,y,z,0,TEMPSUMMON_MANUAL_DESPAWN,0))
                            {
                                pHodir->GetMotionMaster()->MoveRandom();
                            }
                        }

                    }
                    
                if (pTower = m_creature->GetMap()->GetGameObject(m_pInstance->GetData64(GO_TOWER_OF_FLAMES)))
                    if (pTower->HasFlag(GAMEOBJECT_FLAGS,GO_FLAG_DESTROYED))
                    {
                        m_creature->CastSpell(m_creature, SPELL_TOWER_OF_FLAMES_BUFF, true);
                        m_bIsMimironsTower = true;

                        m_creature->SummonCreature(/*MOB_MIMIRON_BEACON*/NPC_FREYA_TARGET_BEACON, mimironInfernoPositions[0].posX,mimironInfernoPositions[0].posY,mimironInfernoPositions[0].posZ,0,TEMPSUMMON_MANUAL_DESPAWN,0);
                    }

                if (pTower = m_creature->GetMap()->GetGameObject(m_pInstance->GetData64(GO_TOWER_OF_LIFE)))
                    if (pTower->HasFlag(GAMEOBJECT_FLAGS,GO_FLAG_DESTROYED))
                    {
                        m_creature->CastSpell(m_creature, SPELL_TOWER_OF_LIFE, true);
                        m_bIsFreyasTower = true;

                        for (uint8 i=0;i<4;++i)
                            m_creature->SummonCreature(MOB_FREYA_BEACON,freyaPositions[i].posX,freyaPositions[i].posY,freyaPositions[i].posZ,0,TEMPSUMMON_MANUAL_DESPAWN,0);

                    }

                if (pTower = m_creature->GetMap()->GetGameObject(m_pInstance->GetData64(GO_TOWER_OF_STORMS)))
                    if (pTower->HasFlag(GAMEOBJECT_FLAGS,GO_FLAG_DESTROYED))
                    {
                        m_creature->CastSpell(m_creature, SPELL_TOWER_OF_STORMS, true);
                        m_bIsThorimsTower = true;

                        float x,y,z;
                        for (uint8 i = 0; i < 7; ++i)
                        {
                            GetRandomPoint(x,y,z,urand(20,60));
                            if (Creature* pThorim = m_creature->SummonCreature(MOB_THORIM_BEACON,x,y,z,0,TEMPSUMMON_MANUAL_DESPAWN,20000))
                            {
                                pThorim->GetMotionMaster()->MoveRandom();
                            }
                        }
                    }
            }
        }

        DoScriptText(SAY_AGGRO, m_creature);
    }

    void GetRandomPoint(float &posX, float &posY, float &posZ, float dist)
    {
        m_creature->GetRandomPoint(m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),dist,posX,posY,posZ);
    }

    void JustDied(Unit *killer)
    {
        if(m_pInstance) 
        {
            m_pInstance->SetData(TYPE_LEVIATHAN, DONE);
            if(m_bIsHardMode)
                m_pInstance->SetData(TYPE_LEVIATHAN_HARD, DONE);
        }

        DoScriptText(SAY_DEATH, m_creature);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_LEVIATHAN, FAIL);
    }

    void KilledUnit(Unit *who)
    {
        DoScriptText(SAY_SLAY, m_creature);
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == MOB_MECHANOLIFT)
            --m_uiMechanoliftCount;
    }

    // TODO: effect 0 and effect 1 may be on different target
    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_PURSUED)
            AttackStart(pTarget);
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        /*if(spell->Id == 62472)
        vehicle->InstallAllAccessories();
        else if(spell->Id == SPELL_ELECTROSHOCK)
        m_creature->InterruptSpell(CURRENT_CHANNELED_SPELL);*/
    }

    void DamageTaken(Unit *pDoneBy, uint32 &uiDamage)
    {
        uiDamage *= 4;
        if(m_creature->HasAura(SPELL_SYSTEMS_SHUTDOWN, EFFECT_INDEX_0))
            uiDamage += uiDamage/2;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // pursue
        if(m_uiPursueTimer < uiDiff)
        {
            switch(urand(0, 3))
            {
                case 0: DoScriptText(SAY_CHANGE1, m_creature); break;
                case 1: DoScriptText(SAY_CHANGE2, m_creature); break;
                case 2: DoScriptText(SAY_CHANGE3, m_creature); break;
            }
            DoScriptText(EMOTE_PURSUE, m_creature);
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                m_creature->DeleteThreatList();
                m_creature->AddThreat(pTarget, 100.0f);
                DoCast(pTarget, SPELL_PURSUED);
            }

            m_uiPursueTimer = 10000;
        }
        else m_uiPursueTimer -= uiDiff;

        // flame vents
        if(m_uiFlameVentsTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_FLAME_VENTS);
            m_uiFlameVentsTimer = 30000 + rand()%20000;
        }
        else 
            m_uiFlameVentsTimer -= uiDiff;

        // battering ram
        if(m_uiBatteringRamTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_BATTERING_RAM);
            m_uiBatteringRamTimer = 25000 + rand()%15000;
        }
        else 
            m_uiBatteringRamTimer -= uiDiff;

        if(m_uiSummonMechanoliftTimer < uiDiff)
        {
            if (m_uiMechanoliftCount < (m_bIsRegularMode ? 10 : 15))
            {
                if (Creature* pLift = m_creature->SummonCreature(MOB_MECHANOLIFT, m_creature->GetPositionX() + rand()%20, m_creature->GetPositionY() + rand()%20, m_creature->GetPositionZ() + 50, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 40000))
                {
                    pLift->GetMotionMaster()->MoveRandom();
                    ++m_uiMechanoliftCount;
                }
            }
            m_uiSummonMechanoliftTimer = m_bIsRegularMode ? 3000 : 2000;
        }
        else m_uiSummonMechanoliftTimer -= uiDiff;

        if(m_uiMissileBarrageTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_MISSILE_BARRAGE);
            m_uiMissileBarrageTimer = 3000 + rand()%2000;
        }
        else 
            m_uiMissileBarrageTimer -= uiDiff;

        if(m_uiGatheringSpeedTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_GATHERING_SPEED);
            m_uiGatheringSpeedTimer = urand(50000, 60000);
        }
        else 
            m_uiGatheringSpeedTimer -= uiDiff;
        DoMeleeAttackIfReady();
    }
};

struct MANGOS_DLL_DECL mob_defense_turretAI : public ScriptedAI
{
    mob_defense_turretAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiSpell_Timer;

    void Reset()
    {
        m_uiSpell_Timer = urand(10000, 15000);
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if(spell->Id == SPELL_SYSTEMS_SHUTDOWN)
            m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSpell_Timer < uiDiff)
        {
            DoCast(m_creature, SPELL_SEARING_FLAME);
            m_uiSpell_Timer = urand(10000, 15000);
        }
        else 
            m_uiSpell_Timer -= uiDiff;
    }
};



/*#######
### NPCs to set/unset hardmode for first boss, needs correct gossip and more reseach, 
### bubble at instance entry should not let players through until they chose leviathan hard/normal mode by talking to brann or the lore keeper.
#######*/

// npc_lore_keeper_of_norgannon_ulduar
#define SET_HARDMODE "Activate secondary defensive systems"

bool GossipHello_npc_lore_keeper_of_norgannon_ulduar(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance *m_pInstance = (ScriptedInstance *) pCreature->GetInstanceData();

    if(m_pInstance && m_pInstance->GetData(TYPE_LEVIATHAN_HARD) != IN_PROGRESS && (m_pInstance->GetData(TYPE_LEVIATHAN) == NOT_STARTED || m_pInstance->GetData(TYPE_LEVIATHAN) == FAIL))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, SET_HARDMODE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_lore_keeper_of_norgannon_ulduar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance *m_pInstance = (ScriptedInstance *) pCreature->GetInstanceData();
    pPlayer->CLOSE_GOSSIP_MENU();

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_LEVIATHAN_HARD, IN_PROGRESS);
    }
    return true;
}

// npc_brann_bronzebeard_ulduar
#define UNSET_HARDMODE "Deactivate secondary defense mechanisms!" // is deactivating hardmode even possible at blizz?

bool GossipHello_npc_brann_bronzebeard_ulduar(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance *m_pInstance = (ScriptedInstance *) pCreature->GetInstanceData();

    if(m_pInstance && m_pInstance->GetData(TYPE_LEVIATHAN_HARD) == IN_PROGRESS && (m_pInstance->GetData(TYPE_LEVIATHAN) == NOT_STARTED || m_pInstance->GetData(TYPE_LEVIATHAN) == FAIL))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, UNSET_HARDMODE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_brann_bronzebeard_ulduar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance *m_pInstance = (ScriptedInstance *) pCreature->GetInstanceData();
    pPlayer->CLOSE_GOSSIP_MENU();

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_LEVIATHAN_HARD, NOT_STARTED);
    }
    return true;
}

/*#######
### at_RX_214_repair_o_matic_station
#######*/
#define EMOTE_REPAIR    "Automatic repair sequence initiated."

bool AreaTrigger_at_RX_214_repair_o_matic_station(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (pPlayer->GetVehicleKit() && pPlayer->GetVehicleKit()->GetBase())
        if(Unit* pVehicle = pPlayer->GetVehicleKit()->GetBase())
        {
            if(!pVehicle->HasAura(SPELL_AUTO_REPAIR))
            {
                pPlayer->MonsterTextEmote(EMOTE_REPAIR, pPlayer, true);
                pPlayer->CastSpell(pVehicle, SPELL_AUTO_REPAIR, true);
            }
        }
    return true;
};

/*#######
### npc_gauntlet_generator
#######*/

const uint32 TowerIDs[] =
{
        GO_STORM_BEACON_1,
        GO_STORM_BEACON_2,
        GO_STORM_BEACON_3,
        GO_STORM_BEACON_4,
        GO_STORM_BEACON_5,
        GO_STORM_BEACON_6,
        GO_STORM_BEACON_7,
        GO_STORM_BEACON_8,
        GO_STORM_BEACON_9,
        GO_STORM_BEACON_10,
        GO_STORM_BEACON_11,
        GO_STORM_BEACON_12,
        GO_STORM_BEACON_13,
        GO_STORM_BEACON_14,
        GO_STORM_BEACON_15,
        GO_STORM_BEACON_16,
        GO_STORM_BEACON_17,
        GO_STORM_BEACON_18,
        GO_STORM_BEACON_19,
        GO_TOWER_OF_FROST,
        GO_TOWER_OF_FLAMES,
        GO_TOWER_OF_LIFE,
        GO_TOWER_OF_STORMS
};

#define TOWER_COUNT 23

struct MANGOS_DLL_DECL npc_gauntlet_generator : public ScriptedAI
{
    npc_gauntlet_generator(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    uint32 m_uiCheckTimer;
    bool m_bIsRegularMode;

    void Reset()
    {
        m_uiCheckTimer = 1000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiCheckTimer < uiDiff)
        {

            // remove spawn if near tower is destroyed
            GameObject *pTower;

            for (uint8 i=0;i<TOWER_COUNT;++i)
                if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, TowerIDs[i], 40.f))
                {
                    pTower = pGo;
                    break;
                }

            if (!pTower || pTower->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_DESTROYED))
            {
                m_creature->ForcedDespawn();
                return;
            }

            Creature* pMob;
            for (uint8 i=0;i<urand(1,m_bIsRegularMode?3:5);++i)
                if (pMob = m_creature->SummonCreature(NPC_STEELFORGE_DEFENDER,m_creature->GetPositionX()+rand()%3,m_creature->GetPositionY()+rand()%3,m_creature->GetPositionZ(),0.f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                    pMob->SetInCombatWithZone();

            m_uiCheckTimer = uint32(urand(10000,20000) * m_bIsRegularMode ? 1 : 0.8);

        }
        else 
            m_uiCheckTimer -= uiDiff;
    }
};

/*#######
### npc_mechanolift
#######*/

struct MANGOS_DLL_DECL npc_mechanolift : public ScriptedAI
{
    npc_mechanolift(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiMoveTimer;

    void Reset()
    {
        m_creature->GetMotionMaster()->MoveRandom();
        m_uiMoveTimer = 0;
    }

    void MovementInform(uint32 /*type*/, uint32 id)
    {
        if (id == 1)
        {
            Creature* pContainer = GetClosestCreatureWithEntry(m_creature, MOB_CONTAINER, 5);
            if (pContainer && m_creature->GetVehicleKit())
                pContainer->EnterVehicle(m_creature->GetVehicleKit());
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiMoveTimer < uiDiff)
        {
            if (m_creature->GetVehicleKit())
                if (m_creature->GetVehicleKit()->HasEmptySeat(0)||m_creature->GetVehicleKit()->HasEmptySeat(1)||m_creature->GetVehicleKit()->HasEmptySeat(2))
                {
                    Creature* pContainer = GetClosestCreatureWithEntry(m_creature,MOB_CONTAINER,50);
                    if (pContainer && !pContainer->GetVehicle())
                        m_creature->GetMotionMaster()->MovePoint(1,pContainer->GetPositionX(),pContainer->GetPositionY(),pContainer->GetPositionZ());
                }
            m_uiMoveTimer = 20000; 
        }
        else
            m_uiMoveTimer -= uiDiff;
    }
};

/*#######
### npc_thorims_hammer
#######*/

struct MANGOS_DLL_DECL npc_thorims_hammer : public ScriptedAI
{
    npc_thorims_hammer(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->setFaction(14);
        m_creature->CastSpell(m_creature, AURA_DUMMY_BLUE, true);
    }

    void AttackStart(Unit*)
    {
        return;
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if ((pWho->IsVehicle() || pWho->GetTypeId() == TYPEID_PLAYER) && m_creature->IsInRange(pWho,0,10,false))
        {
            if (Creature* pTrigger = m_creature->SummonCreature(NPC_THORIM_TARGET_BEACON, pWho->GetPositionX()+rand()%5,pWho->GetPositionY()+rand()%5,pWho->GetPositionZ(),0,TEMPSUMMON_TIMED_DESPAWN,2000))
                m_creature->CastSpell(pTrigger, SPELL_THORIMS_HAMMER_MISSILE, true);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        ScriptedAI::UpdateAI(uiDiff);
        if (!m_creature->HasAura(AURA_DUMMY_BLUE))
            m_creature->CastSpell(m_creature, AURA_DUMMY_BLUE, true);
    }
};

/*#######
### npc_mimirons_inferno
#######*/

struct MANGOS_DLL_DECL npc_mimirons_inferno : public ScriptedAI
{
    npc_mimirons_inferno(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiInfernoTimer;

    void Reset()
    {
        m_uiInfernoTimer = 2000;
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, AURA_DUMMY_YELLOW, true);
    }

    void AttackStart(Unit*)
    {
        return;
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type == POINT_MOTION_TYPE)
        {   
            m_creature->GetMotionMaster()->MovePoint(id==3?0:++id,mimironInfernoPositions[id].posX,mimironInfernoPositions[id].posY,mimironInfernoPositions[id].posZ);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->HasAura(AURA_DUMMY_YELLOW))
            m_creature->CastSpell(m_creature,AURA_DUMMY_YELLOW,true);

        if(m_uiInfernoTimer <= uiDiff)
        {
            if (Creature* pTrigger = m_creature->SummonCreature(NPC_MIMIRON_TARGET_BEACON, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 2000))
            {
                m_creature->CastSpell(pTrigger, SPELL_MIMIRON_INF_MISSILE, true);
                m_uiInfernoTimer = 2000;
            }
        }
        else
            m_uiInfernoTimer -= uiDiff;

    }
};


/*#######
### npc_hodirs_fury
#######*/

struct MANGOS_DLL_DECL npc_hodirs_fury : public ScriptedAI
{
    npc_hodirs_fury(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    void Reset()
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, AURA_DUMMY_GREEN, true);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if ((pWho->IsVehicle() || pWho->GetTypeId() == TYPEID_PLAYER) && m_creature->IsInRange(pWho,0,5,false))
        {
            if (Creature* pTrigger = m_creature->SummonCreature(NPC_HODIR_TARGET_BEACON, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(),0,TEMPSUMMON_TIMED_DESPAWN,1000))
                m_creature->CastSpell(pTrigger, SPELL_HODIRS_FURY_MISSILE, true);
        }
    }

    void UpdateAI(const uint32 /*diff*/)
    {
        if (!m_creature->HasAura(AURA_DUMMY_GREEN))
            m_creature->CastSpell(m_creature, AURA_DUMMY_GREEN, true);
    }

};

/*#######
### npc_freyas_ward
#######*/

struct MANGOS_DLL_DECL npc_freyas_ward : public ScriptedAI
{
    npc_freyas_ward(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    uint32 m_uiSummonTimer;
    bool m_bIsRegularMode;

    void Reset()
    {
        m_creature->setFaction(14);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
        m_creature->CastSpell(m_creature, AURA_DUMMY_GREEN, true);
        m_uiSummonTimer = 2000;
    }

    void AttackStart(Unit*)
    {
        return;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->HasAura(AURA_DUMMY_GREEN))
            m_creature->CastSpell(m_creature, AURA_DUMMY_GREEN, true);

        if (m_uiSummonTimer < uiDiff)
        {
            m_creature->CastSpell(m_creature,SPELL_FREYAS_WARD_MISSILE,true);
            for (uint8 i=0;i<urand(1,m_bIsRegularMode?3:5);++i)
                m_creature->CastSpell(m_creature,(rand()%2)?SPELL_SUMMON_LASHER:SPELL_SUMMON_WARD,true);
            m_uiSummonTimer = urand(10000,20000);
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

/*#######
### npc_freya_ward_summon
#######*/

enum
{
    SPELL_LASH = 65062,
};

struct MANGOS_DLL_DECL npc_freya_ward_summon : public ScriptedAI
{
    npc_freya_ward_summon(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiCastTimer;
    bool m_bIsRegularMode;

    void Reset()
    {
        m_creature->setFaction(14);
        m_uiCastTimer = 2000;
        m_creature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiCastTimer < uiDiff)
        {
            m_creature->CastSpell(m_creature->getVictim(),SPELL_LASH,false);
            m_uiCastTimer = urand(3000,8000);
        }
        else
            m_uiCastTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_defense_turret(Creature* pCreature)
{
    return new mob_defense_turretAI(pCreature);
}

CreatureAI* GetAI_boss_flame_leviathan(Creature* pCreature)
{
    return new boss_flame_leviathan(pCreature);
}

CreatureAI* GetAI_npc_gauntlet_generator(Creature* pCreature)
{
    return new npc_gauntlet_generator(pCreature);
}

CreatureAI* GetAI_npc_mechanolift(Creature* pCreature)
{
    return new npc_mechanolift(pCreature);
}

CreatureAI* GetAI_npc_thorims_hammer(Creature* pCreature)
{
    return new npc_thorims_hammer(pCreature);
}

CreatureAI* GetAI_npc_mimirons_inferno(Creature* pCreature)
{
    return new npc_mimirons_inferno(pCreature);
}

CreatureAI* GetAI_npc_hodirs_fury(Creature* pCreature)
{
    return new npc_hodirs_fury(pCreature);
}

CreatureAI* GetAI_npc_freyas_ward(Creature* pCreature)
{
    return new npc_freyas_ward(pCreature);
}

CreatureAI* GetAI_npc_freya_ward_summon(Creature* pCreature)
{
    return new npc_freya_ward_summon(pCreature);
}

void AddSC_boss_leviathan()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_flame_leviathan";
    pNewScript->GetAI = &GetAI_boss_flame_leviathan;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_defense_turret";
    pNewScript->GetAI = &GetAI_mob_defense_turret;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_lore_keeper_of_norgannon_ulduar";
    pNewScript->pGossipHello = &GossipHello_npc_lore_keeper_of_norgannon_ulduar;
    pNewScript->pGossipSelect = &GossipSelect_npc_lore_keeper_of_norgannon_ulduar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_brann_bronzebeard_ulduar";
    pNewScript->pGossipHello = &GossipHello_npc_brann_bronzebeard_ulduar;
    pNewScript->pGossipSelect = &GossipSelect_npc_brann_bronzebeard_ulduar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_RX_214_repair_o_matic_station";
    pNewScript->pAreaTrigger = &AreaTrigger_at_RX_214_repair_o_matic_station;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_gauntlet_generator";
    pNewScript->GetAI = &GetAI_npc_gauntlet_generator;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_mechanolift";
    pNewScript->GetAI = &GetAI_npc_mechanolift;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_thorims_hammer";
    pNewScript->GetAI = &GetAI_npc_thorims_hammer;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "npc_mimirons_inferno";
    pNewScript->GetAI = &GetAI_npc_mimirons_inferno;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_hodirs_fury";
    pNewScript->GetAI = &GetAI_npc_hodirs_fury;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_freyas_ward";
    pNewScript->GetAI = &GetAI_npc_freyas_ward;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_freya_ward_summon";
    pNewScript->GetAI = &GetAI_npc_freya_ward_summon;
    pNewScript->RegisterSelf();   
}
