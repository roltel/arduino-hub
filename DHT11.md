# Introduction #

The DHT11 is a relatively cheap sensor for measuring temperature and humidity. This article describes a small library for reading both from the sensor. The DHT22 is similar to the DHT11 and has greater accuracy. However, this library is not suitable for the DHT21 or DHT22 as they have a different data format. Check DHTlib for support of these sensors.

This library is tested on a MEGA2560 and is confirmed working on an Arduino 2009.

Niesteszeck has made an interrupt-driven library for the DHT11 sensor.

Andy Dalton has made a modified version. Difference is that the DATAPIN is defined in the constructor, resulting in one dedicated object per sensor.

# Connection #

The DHT11 has three lines: GND, +5V and a single data line. By means of a handshake, the values are clocked out over the single digital line.

Datasheet: http://www.micro4you.com/files/sensor/DHT11.pdf

3 pins break out shield version - http://www.geeetech.com/wiki/index.php/Electric_thermometer_by_using_DHT11_sensor_module

## Sources ##