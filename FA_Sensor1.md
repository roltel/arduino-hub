# Introduction #

Arduino Weather Station (Datalog to SD + To Sever Mysql/PHP). This is a Arduino project that records the values of a sensor DHT11, a BMP085 and LDR.

The Arduino code calculates the Dew point, and records all data on a SD card first. For recording on the SD we used a RTC so we could have a timestamp on the datalog.txt. After recording the data on SD Card, the code will save the data on a mysql/php server.

We used 2 files (conec.php and add.php) php to save the data coming from the Arduino to the Mysql Database.


# Details #

Components:
  * Arduino Ethernet;
  * Sensor DHT11;
  * Sensor BMP085;
  * LDR;
  * Real Time Code;

## The PHP/Mysql Code ##
First create a database on your mysql server with the tables you need.

Then create two files on your webserver:

File: conec.php

File: add.php

## The Arduino Code ##

Temporary Link: https://code.google.com/p/arduino-hub/source/browse/trunk/sketches/FA_Sensor1_Zeta_final/FA_Sensor1_Zeta_final.ino