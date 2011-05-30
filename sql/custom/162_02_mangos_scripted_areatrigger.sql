-- Instance Ulduar
DELETE FROM `scripted_areatrigger` WHERE `entry` IN ('5369','5423');
INSERT INTO `scripted_areatrigger` (`entry`,`ScriptName`) VALUES 
('5369', 'at_RX_214_repair_o_matic_station'),
('5423', 'at_RX_214_repair_o_matic_station');
