-- Eye of Acherus ("Death comes from on high") Script Texts

UPDATE `script_texts` SET `content_loc3` = "Das Auge von Acherus bewegt sich auf sein Ziel zu." WHERE `entry` = '-1666451';
UPDATE `script_texts` SET `content_loc3` = "Das Auge von Acherus unterliegt Eurer Kontrolle." WHERE `entry` = '-1666452';

-- Scarlet Courier

DELETE FROM `script_texts` WHERE `entry` IN ('-1609531','-1609532');
INSERT INTO `script_texts`
    (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
    (-1609531, 'Hrm, what a strange tree. I must investigate.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'Scarlet Courier SAY_TREE1'),
    (-1609532, 'What\'s this!? This isn\'t a tree at all! Guards! Guards!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'Scarlet Courier SAY_TREE2');

-- Quest The Might of the Horde

DELETE FROM `script_texts` WHERE `entry` IN (-1999890,-1999889,-1999888);
INSERT INTO `script_texts`
    (`entry`, `content_default`, `type`, `comment`)
VALUES
    (-1999890,'Anub\'ar fear nothing, mortal...',0,'npc_warsong_battle_standart SAY_INVIDER_DESTROYED_STANDARD'),
    (-1999889,'The Anub\'ar have destroyed Warsong Battle Standard!',2,'npc_warsong_battle_standart SAY_EMOTE_STANDARD_DESTROYED'),
    (-1999888,'Show yourselves so that I may crack your insectoid skeletons with my bare hands!',0,'npc_warsong_battle_standart SAY_PLAYER_PLANTED_STANDARD');
