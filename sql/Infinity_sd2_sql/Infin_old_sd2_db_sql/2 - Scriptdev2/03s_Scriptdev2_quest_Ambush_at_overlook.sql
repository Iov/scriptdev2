-- FallenAngelX
ALTER TABLE db_version_infinitysd2_update CHANGE COLUMN r02 r03 bit;
 
-- sql content between the lines --------------  start

-- Ambush At The Overlook
DELETE FROM script_texts WHERE entry BETWEEN -1609121 AND -1609120;
INSERT INTO `script_texts` (`entry`,`content_default`,`sound`,`type`,`language`,`emote`,`comment`) VALUES
   (-1609120, 'Hmm, what a strange tree. I must investigate.',0,0,0,0,'Scarlet Courier SAY_TREE1'),
   (-1609121, 'What''s this!? This isn''t a tree at all! Guards! Guards!',0,0,0,0,'Scarlet Courier SAY_TREE2');

-- sql content between the lines -------------- end

REPLACE INTO `db_version_infinitysd2_update` (`version`) VALUES ('r03');