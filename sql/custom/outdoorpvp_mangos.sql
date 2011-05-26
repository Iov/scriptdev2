UPDATE gameobject_template SET ScriptName='go_silithyst' WHERE entry IN (181597,181598);
DELETE FROM scripted_areatrigger WHERE entry IN (4162,4168);
INSERT INTO scripted_areatrigger VALUES 
(4162,'at_silithus'),
(4168,'at_silithus');
UPDATE world_template SET scriptName='worldmap_kalimdor' WHERE map=1;

UPDATE world_template SET scriptName='worldmap_eastern_kingdoms' WHERE map=0;
DELETE FROM scripted_event_id WHERE id IN (10567,10564,10687,10688,10701,10700,11153,11152);
INSERT INTO scripted_event_id VALUES
(10567,'event_plaguewood_tower'),
(10564,'event_plaguewood_tower'),
(10687,'event_plaguewood_tower'),
(10688,'event_plaguewood_tower'),
(10701,'event_plaguewood_tower'),
(10700,'event_plaguewood_tower'),
(11153,'event_plaguewood_tower'),
(11152,'event_plaguewood_tower');

UPDATE world_template SET scriptName='worldmap_outland' WHERE map=530;
DELETE FROM scripted_event_id WHERE id IN (11406,11405,11400,11399,11404,11403,11402,11401);
INSERT INTO scripted_event_id VALUES
(11406,'event_broken_hill_tower'),
(11405,'event_broken_hill_tower'),
(11400,'event_broken_hill_tower'),
(11399,'event_broken_hill_tower'),
(11404,'event_broken_hill_tower'),
(11403,'event_broken_hill_tower'),
(11402,'event_broken_hill_tower'),
(11401,'event_broken_hill_tower');
DELETE FROM scripted_event_id WHERE id IN (11390,11389,11384,11383,11388,11387,11386,11385);
INSERT INTO scripted_event_id VALUES
(11390,'event_stadium_tower'),
(11389,'event_stadium_tower'),
(11384,'event_stadium_tower'),
(11383,'event_stadium_tower'),
(11388,'event_stadium_tower'),
(11387,'event_stadium_tower'),
(11386,'event_stadium_tower'),
(11385,'event_stadium_tower');
DELETE FROM scripted_event_id WHERE id IN (11398,11397,11392,11391,11396,11395,11394,11393);
INSERT INTO scripted_event_id VALUES
(11398,'event_overlook_tower'),
(11397,'event_overlook_tower'),
(11392,'event_overlook_tower'),
(11391,'event_overlook_tower'),
(11396,'event_overlook_tower'),
(11395,'event_overlook_tower'),
(11394,'event_overlook_tower'),
(11393,'event_overlook_tower');