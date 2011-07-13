-- DK Ghoul (Raise Dead & Army of the Dead)

UPDATE `creature_template` SET `ScriptName` = "pet_dk_ghoul" WHERE `entry` IN (26125, 24207);

-- Training Dummy

UPDATE `creature_template` SET `AIName` = 'EventAI', `flags_extra` = '2', `unit_flags` = '393220', `mechanic_immune_mask` = '4399133',  `ScriptName` = 'npc_training_dummy' WHERE `entry` IN (32666, 33229, 33243, 33272, 31146, 32667, 31144, 25225, 32666, 5652, 17578, 19139, 17059, 17060, 2673, 18504, 32542, 32546, 32545, 32543, 1921, 18504, 16211, 5202, 27222, 27223, 32541);

-- ScriptName's for Quest Massacre at Light's Point

UPDATE `creature_template` SET `ScriptName` = 'npc_mine_car' WHERE `entry` = '28817';
UPDATE `creature_template` SET `ScriptName` = 'npc_scarlet_miner' WHERE `entry` = '28841';

-- Instance gundrak

UPDATE `creature_template` SET `ScriptName` = 'boss_colossus' WHERE `entry` = '29307';
UPDATE `creature_template` SET `ScriptName` = 'boss_elemental' WHERE `entry` = '29573';
UPDATE `creature_template` SET `ScriptName` = 'npc_living_mojo' WHERE `entry` = '29830';

-- Thargold Ironwing

UPDATE `creature_template` SET `ScriptName`='npc_thargold_ironwing' WHERE `entry`='29154';

-- Thirst Unending

UPDATE `creature_template` SET `ScriptName`='npc_mana_wyrm' WHERE `entry`='15274';

-- Feast of Winter Veil Fixes

UPDATE `creature_template` SET `ScriptName` = 'npc_winter_reveler' WHERE `entry`='15760';
UPDATE `creature_template` SET `ScriptName` = 'npc_metzen', `npcflag` = '1' WHERE entry = '15664';

-- ScriptName's and Walk Speed for Escort Gryphon (Massacre at Light's Point)

UPDATE `creature_template` SET `speed_walk`='2.7', `speed_run`='2.7', `ScriptName`='npc_scourge_gryphon' WHERE `entry`='28864';

-- NPC Slag in instance Halls of Lightning

UPDATE `creature_template` SET `ScriptName`='npc_slag' WHERE `entry`='28585';

-- Instance Ahn'kahet

UPDATE `creature_template` SET `ScriptName` = 'mob_flame_orb' WHERE `entry` = '30702';
UPDATE `creature_template` SET `ScriptName` = 'npc_twilight_volunteer' WHERE `entry` = '30385';
UPDATE `creature_template` SET `ScriptName` = 'mob_volazj_clone' WHERE `entry` IN ('30621', '30622', '30623', '30624', '30625');
UPDATE `creature_template` SET `ScriptName` = 'boss_volazj' WHERE `entry` = '29311';

-- Instance Naxxramas

UPDATE `creature_template` SET `ScriptName` = 'mob_crypt_guard', `AIName` = '' WHERE `entry` = '16573';
UPDATE `creature_template` SET `ScriptName` = 'npc_grobbulus_poison_cloud' WHERE `entry` = '16363';
UPDATE `creature_template` SET `ScriptName` = 'boss_stalagg', `AIName` = '' WHERE `entry` = '15929';
UPDATE `creature_template` SET `ScriptName` = 'boss_feugen', `AIName` = '' WHERE `entry` = '15930';
UPDATE `creature_template` SET `ScriptName` = 'boss_thaddius', `AIName` = '' WHERE `entry` = '15928';
UPDATE `creature_template` SET `ScriptName` = 'npc_obedience_crystal' WHERE `entry` = '29912';
UPDATE `creature_template` SET `ScriptName` = 'mob_void_zone_naxx' WHERE `entry` = '16697';

-- ScriptName for Val'Kyr Resurrection Event in Ebon Hold

UPDATE `creature_template` SET `ScriptName` = 'npc_valkyr_battle_maiden' WHERE `entry` = '28534';

-- Death comes from on high (Quest - 12641)

UPDATE `creature_template` SET `spell1` = '52006', `spell2` = '51859', `spell3` = '51904', `spell4` = '52694', `spell5` = '0', `InhabitType` = '3', `ScriptName` = 'npc_eye_of_acherus' WHERE `entry` = '28511';

-- Instance Nexus

UPDATE `creature_template` SET `ScriptName` = 'mob_crystal_spike' WHERE `entry` = '27099';
UPDATE `creature_template` SET `ScriptName` = 'mob_crystalline_tangler' WHERE `entry` = '32665';
UPDATE `creature_template` SET `ScriptName` = 'npc_chaotic_rift' WHERE `entry` = '26918';

-- Instance Utgarde Keep

UPDATE `creature_template` SET `ScriptName` = 'mob_frost_tomb' WHERE `entry` = '23965';
UPDATE `creature_template` SET `ScriptName` = 'mob_ingvar_throw_dummy' WHERE `entry` = '23997';

-- Instance Halls of Stone

UPDATE `creature_template` SET `ScriptName` = 'mob_tribuna_controller' WHERE `entry` = '28234';

-- Instance Eye of Eternity

UPDATE `creature_template` SET `AIName` = 'NullAI' WHERE `entry` = '30282';

-- Experience Eliminator

UPDATE `creature_template` SET `ScriptName` = "npc_experience_eliminator" WHERE `entry` IN (35365,35364);

-- Noblegarden Spring Fling

UPDATE `creature_template` SET `ScriptName`='pet_spring_rabbit' WHERE `entry`='32791';

-- Childrens Week Orphans

UPDATE `creature_template` SET `ScriptName`='pet_orphan' WHERE `entry` IN(33532,33533);

-- Quest Cold Hearted

UPDATE `creature_template` SET `ScriptName`='npc_brunnhildar_prisoner' WHERE `entry`='29639';
UPDATE `creature_template` SET `ScriptName`='npc_freed_protodrake', `flags_extra`='4096' WHERE `entry`='29709';

-- Quest The Warm Up

UPDATE `creature_template` SET `ScriptName`='npc_kirgaraak' WHERE `entry`='29352';
UPDATE `creature_template` SET `spell1`='54459', `spell2`='54458', `spell3`='54460' WHERE `entry`='29918';

-- Quest Plagued Lands

UPDATE `creature_template` SET `ScriptName`='npc_captured_rabid_thistle_bear' WHERE `entry`='11836';
UPDATE `creature_template` SET `ScriptName`='npc_rabid_thistle_bear' WHERE `entry`='2164';

-- Instance Utgarde Pinnacle

UPDATE `creature_template` SET `ScriptName` = 'npc_spectator' WHERE `entry` = '26667';
UPDATE `creature_template` SET `AIName` = 'NUllAI' WHERE `entry` = '27327';
UPDATE `creature_template` SET `ScriptName` = 'mob_spirit_fount' WHERE `entry` = '27339';

-- Quest The Last of her kind

UPDATE `creature_template` SET `ScriptName`='npc_harnessed_icemaw_matriarch', `flags_extra`='4098' WHERE `entry`='30468';


-- Quest Ambush at the Overlook

UPDATE `creature_template` SET `ScriptName`='mob_scarlet_courier' WHERE `entry`='29076';

-- Instance Forge of Souls

UPDATE `creature_template` SET `ScriptName`='npc_corrupted_soul_fragment' WHERE `entry`='36535';

-- Quest The Might of the Horde

UPDATE `creature_template` SET `ScriptName`='npc_warsong_battle_standart' WHERE `entry`='26678';

-- Quests Reunited and Dark Horizon

UPDATE `creature_template` SET `ScriptName`='npc_flying_fiend_vehicle', `InhabitType`='4' WHERE `entry`='28669';

-- Instance Ulduar
-- UPDATE `creature_template` SET `ScriptName` = 'boss_flame_leviathan_seat' WHERE `entry` = '33114'; -- not scripted yet
-- UPDATE `creature_template` SET `ScriptName` = 'boss_flame_leviathan_overload_device' WHERE `entry` = '33143'; -- not scripted yet
UPDATE `creature_template` SET `ScriptName` = 'npc_thorims_hammer' WHERE `entry` = '33365';
UPDATE `creature_template` SET `ScriptName` = 'npc_mimirons_inferno' WHERE `entry` = '33366'; -- should be 33370, but that one is already assigned in boss mirimon fight
UPDATE `creature_template` SET `ScriptName` = 'npc_hodirs_fury' WHERE `entry` = '33212';
UPDATE `creature_template` SET `ScriptName` = 'npc_freyas_ward' WHERE `entry` = '33367';
UPDATE `creature_template` SET `ScriptName` = 'npc_lore_keeper_of_norgannon_ulduar' WHERE `entry` = '33686';
UPDATE `creature_template` SET `ScriptName` = 'npc_brann_bronzebeard_ulduar' WHERE `entry` = '33579';
UPDATE `creature_template` SET `ScriptName` = 'npc_freya_ward_summon' WHERE `entry` IN ('34275','33387');
UPDATE `creature_template` SET `ScriptName` = 'npc_mechanolift' WHERE `entry` = '33214';
UPDATE `creature_template` SET `ScriptName` = 'npc_gauntlet_generator' WHERE `entry` = '33571';
