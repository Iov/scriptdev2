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

-- Quests Reunited and Dark Horizon

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1999810 AND -1999805;
INSERT INTO `script_texts`
     (`entry`,`content_default`,`content_loc1`,`content_loc2`,`content_loc3`,`content_loc4`,`content_loc5`,`content_loc6`,`content_loc7`,`content_loc8`,`sound`,`type`,`language`,`emote`,`comment`)
VALUES
    (-1999810,'Come to me now, $n. I must be speakin\' wit ya.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,4,0,0,'npc_flying_fiend_vehicle'),
    (-1999809,'Da Lich King be sharin\' his power wit dem who serve him well, mon.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,4,0,0,'npc_flying_fiend_vehicle'),
    (-1999808,'Study dis place, mon. Ya gonna be helpin\' me conquest it!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,4,0,0,'npc_flying_fiend_vehicle'),
    (-1999807,'Ahh, dere be our destiny... Gundrak',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,4,0,0,'npc_flying_fiend_vehicle'),
    (-1999806,'Here, da self-righteous crusaders be standin\' in da wayout of goal. Day will fall!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,4,0,0,'npc_flying_fiend_vehicle'),
    (-1999805,'A portion of this land already be mine, mon, but it only be da beginning!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,4,0,0,'npc_flying_fiend_vehicle');
