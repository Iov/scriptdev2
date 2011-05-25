-- FallenAngelX
ALTER TABLE db_version_infinitysd2_update CHANGE COLUMN r00 r01 bit;
 
-- sql content between the lines --------------  start

-- blah blah blah  i am data that goes here 

-- sql content between the lines -------------- end

REPLACE INTO `db_version_infinitysd2_update` (`version`) VALUES ('r01');