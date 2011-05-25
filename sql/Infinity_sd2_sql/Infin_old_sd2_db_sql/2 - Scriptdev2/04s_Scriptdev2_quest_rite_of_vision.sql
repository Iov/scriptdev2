-- FallenAngelX
ALTER TABLE db_version_infinitysd2_update CHANGE COLUMN r03 r04 bit;
 
-- sql content between the lines --------------  start

-- Rite of Vision

DELETE FROM script_waypoint WHERE entry=2983;

INSERT INTO script_waypoint
   (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`)
VALUES
   ( 2983, 1, -2226.32,  -408.095,   -9.36235, 0, 'Plains Vision Waypoint'),
   ( 2983, 2, -2203.04,  -437.212,   -5.72498, 0, 'Plains Vision Waypoint'),
   ( 2983, 3, -2163.91,  -457.851,   -7.09049, 0, 'Plains Vision Waypoint'),
   ( 2983, 4, -2123.87,  -448.137,   -9.29591, 0, 'Plains Vision Waypoint'),
   ( 2983, 5, -2104.66,  -427.166,   -6.49513, 0, 'Plains Vision Waypoint'),
   ( 2983, 6, -2101.48,  -422.826,   -5.3567, 0, 'Plains Vision Waypoint'),
   ( 2983, 7, -2097.56,  -417.083,   -7.16716, 0, 'Plains Vision Waypoint'),
   ( 2983, 8, -2084.87,  -398.626,   -9.88973, 0, 'Plains Vision Waypoint'),
   ( 2983, 9, -2072.71,  -382.324,   -10.2488, 0, 'Plains Vision Waypoint'),
   ( 2983, 10, -2054.05,  -356.728,   -6.22468, 0, 'Plains Vision Waypoint'),
   ( 2983, 11, -2051.8,   -353.645,   -5.35791, 0, 'Plains Vision Waypoint'),
   ( 2983, 12, -2049.08,  -349.912,   -6.15723, 0, 'Plains Vision Waypoint'),
   ( 2983, 13, -2030.6,   -310.724,   -9.59302, 0, 'Plains Vision Waypoint'),
   ( 2983, 14, -2002.15,  -249.308,   -10.8124, 0, 'Plains Vision Waypoint'),
   ( 2983, 15, -1972.85,  -195.811,   -10.6316, 0, 'Plains Vision Waypoint'),
   ( 2983, 16, -1940.93,  -147.652,   -11.7055, 0, 'Plains Vision Waypoint'),
   ( 2983, 17, -1888.06,  -81.943,    -11.4404, 0, 'Plains Vision Waypoint'),
   ( 2983, 18, -1837.05,  -34.0109,   -12.258, 0, 'Plains Vision Waypoint'),
   ( 2983, 19, -1796.12,  -14.6462,   -10.3581, 0, 'Plains Vision Waypoint'),
   ( 2983, 20, -1732.61,  -4.27746,   -10.0213, 0, 'Plains Vision Waypoint'),
   ( 2983, 21, -1688.94,  -0.829945,  -11.7103, 0, 'Plains Vision Waypoint'),
   ( 2983, 22, -1681.32,  13.0313,    -9.48056, 0, 'Plains Vision Waypoint'),
   ( 2983, 23, -1677.04,  36.8349,    -7.10318, 0, 'Plains Vision Waypoint'),
   ( 2983, 24, -1675.2,   68.559,     -8.95384, 0, 'Plains Vision Waypoint'),
   ( 2983, 25, -1676.57,  89.023,     -9.65104, 0, 'Plains Vision Waypoint'),
   ( 2983, 26, -1678.16,  110.939,    -10.1782, 0, 'Plains Vision Waypoint'),
   ( 2983, 27, -1677.86,  128.681,    -5.73869, 0, 'Plains Vision Waypoint'),
   ( 2983, 28, -1675.27,  144.324,    -3.47916, 0, 'Plains Vision Waypoint'),
   ( 2983, 29, -1671.7,   163.169,    -1.23098, 0, 'Plains Vision Waypoint'),
   ( 2983, 30, -1666.61,  181.584,    5.26145, 0, 'Plains Vision Waypoint'),
   ( 2983, 31, -1661.51,  196.154,    8.95252, 0, 'Plains Vision Waypoint'),
   ( 2983, 32, -1655.47,  210.811,    8.38727, 0, 'Plains Vision Waypoint'),
   ( 2983, 33, -1647.07,  226.947,    5.27755, 0, 'Plains Vision Waypoint'),
   ( 2983, 34, -1621.65,  232.91,     2.69579, 0, 'Plains Vision Waypoint'),
   ( 2983, 35, -1600.23,  237.641,    2.98539, 0, 'Plains Vision Waypoint'),
   ( 2983, 36, -1576.07,  242.546,    4.66541, 0, 'Plains Vision Waypoint'),
   ( 2983, 37, -1554.57,  248.494,    6.60377, 0, 'Plains Vision Waypoint'),
   ( 2983, 38, -1547.53,  259.302,    10.6741, 0, 'Plains Vision Waypoint'),
   ( 2983, 39, -1541.7,   269.847,    16.4418, 0, 'Plains Vision Waypoint'),
   ( 2983, 40, -1539.83,  278.989,    21.0597, 0, 'Plains Vision Waypoint'),
   ( 2983, 41, -1540.16,  290.219,    27.8247, 0, 'Plains Vision Waypoint'),
   ( 2983, 42, -1538.99,  298.983,    34.0032, 0, 'Plains Vision Waypoint'),
   ( 2983, 43, -1540.38,  307.337,    41.3557, 0, 'Plains Vision Waypoint'),
   ( 2983, 44, -1536.61,  314.884,    48.0179, 0, 'Plains Vision Waypoint'),
   ( 2983, 45, -1532.42,  323.277,    55.6667, 0, 'Plains Vision Waypoint'),
   ( 2983, 46, -1528.77,  329.774,    61.1525, 0, 'Plains Vision Waypoint'),
   ( 2983, 47, -1525.65,  333.18,     63.2161, 0, 'Plains Vision Waypoint'),
   ( 2983, 48, -1517.01,  350.713,    62.4286, 0, 'Plains Vision Waypoint'),
   ( 2983, 49, -1511.39,  362.537,    62.4539, 0, 'Plains Vision Waypoint'),
   ( 2983, 50, -1508.68,  366.822,    62.733, 0, 'Plains Vision Waypoint');
   
-- sql content between the lines -------------- end

REPLACE INTO `db_version_infinitysd2_update` (`version`) VALUES ('r04');