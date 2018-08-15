#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"

#define DHTPIN  A1     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4

DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

 #include <SPI.h>
#include <Ethernet.h>
// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "lab.futuragora.pt";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,0,21);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

#include <Wire.h>



double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

// fast integer 3vversion with rounding
//int Celcius2Fahrenheit(int celcius)
//{
//  return (celsius * 18 + 5)/10 + 32;
//}


//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
  return celsius + 273.15;
}

// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

        // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

        // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP/0.61078);   // temp var
  return (241.88 * T) / (17.558 - T);
}

// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}





void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  dht.begin();

  // if you get a connection, report back via serial:
  if (client.connect(server, 89)) {
    Serial.println("conection test");
    // disconnecting from server
       Serial.println("disconnecting.");
    client.stop();
    
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
}
  
void loop() 
{
float h = dht.readHumidity();
 {
   if (client.connect(server, 80)) {
      
      
 // sendig data to server   
 // Serial.println("connected send");
    client.print("GET http://lab.futuragora.pt:80/opensenses/fasensor5/add.php?");
    client.print("temperature=");    
    client.print(bmp.readTemperature());
    client.print("&&");
    client.print("pressure=");
    client.print(bmp.readPressure());
    client.print("&&");
   client.print("humidity=");
   client.print(h);
 //    client.print("&&");
 //  client.print("temperature2=");
 //  client.print((float)DHT11.temperature, 2);
 //       client.print("&&");
//   client.print("dew=");
//   client.print(dewPointFast(DHT11.temperature, DHT11.humidity));
  // client.print("&&");
  // client.print("light=");
  // client.print(LDRReading);
    client.println();
    client.println();
    
// disconnecting from server
 //   Serial.println("disconnecting. send");
    client.stop();
 }
 else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed"); 
 } 
 }
 
 {  
   delay(59550);
}
}
