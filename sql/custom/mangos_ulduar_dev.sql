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

DELETE FROM `scripted_areatrigger` WHERE `entry` IN ('5369','5423');
INSERT INTO `scripted_areatrigger` (`entry`,`ScriptName`) VALUES 
('5369', 'at_RX_214_repair_o_matic_station'),
('5423', 'at_RX_214_repair_o_matic_station');
