-- FallenAngelX
ALTER TABLE db_version_infinitysd2_update CHANGE COLUMN r05 r06 bit;
 
-- sql content between the lines --------------  start

DELETE FROM `script_waypoint` WHERE `entry`='29709';

INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`) VALUES 
('29709', '0', '7250.15', '-2327.22', '869.03'),
('29709', '1', '7118.79', '-2122.05', '841.32'),
('29709', '2', '7052.86', '-1905.99', '888.59'),
('29709', '3', '7038.24', '-1822.77', '857.94'),
('29709', '4', '7044.09', '-1792.25', '841.69'),
('29709', '5', '7071.20', '-1780.73', '822.62');
   
-- sql content between the lines -------------- end

REPLACE INTO `db_version_infinitysd2_update` (`version`) VALUES ('r06');