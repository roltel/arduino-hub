/* 
Project: FA_Sensor1 
Creator: Futuragora
Date: 31/12/13
Components: Arduino Ehternet,DHT11,BMP085,RTC
 
	 
 */

 
 
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "dev.futuragora.pt";    // name address for Google (using DNS)
IPAddress ip(192,168,1,177);
EthernetClient client;

 
#include <Adafruit_BMP085.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
 #include <dht11.h>

dht11 DHT11;

#define DHT11PIN 6

RTC_DS1307 rtc;
int LDR_Pin = A0;
Adafruit_BMP085 bmp;

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
const int chipSelect = 4;



double Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}
double Kelvin(double celsius)
{
	return celsius + 273.15;
}
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
double dewPointFast(double celsius, double humidity)
{
	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	double Td = (b * temp) / (a - temp);
	return Td;
}


void setup()
{
  Serial.begin(9600);
{  
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); 
#endif
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
} 
      if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
   while (!Serial) {
    ; 
  }
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");

    Ethernet.begin(mac, ip);
  }

  delay(1000);
  Serial.println("connecting...");

  if (client.connect(server, 89)) {
    Serial.println("Connection to server success.");

    client.stop();
    
  } 
  else {
    Serial.println("Connection failed.");
  }
  
  // fim de parte enviar

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present.");
    // don't do anything more:
    return;
  }
  Serial.println("Card initialized.");
}



void loop()
{
      DateTime now = rtc.now();
int LDRReading = analogRead(LDR_Pin); 
 int chk = DHT11.read(DHT11PIN);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
     dataFile.print(now.year(), DEC);
     dataFile.print('-');
     dataFile.print(now.month(), DEC);
     dataFile.print('-');
     dataFile.print(now.day(), DEC);
     dataFile.print(' ');
     dataFile.print(now.hour(), DEC);
     dataFile.print(':');
     dataFile.print(now.minute(), DEC);
     dataFile.print(':');
     dataFile.print(now.second(), DEC);
     dataFile.print(',');
     dataFile.print(bmp.readTemperature());
     dataFile.print(",");    
     dataFile.print(bmp.readPressure());
     dataFile.print(",");    
     dataFile.print(DHT11.humidity);
     dataFile.print(",");    
     dataFile.print(DHT11.temperature);
     dataFile.print(",");    
     dataFile.print(dewPointFast(DHT11.temperature, DHT11.humidity));
     dataFile.print(",");
     dataFile.println(LDRReading);
     dataFile.close();
     Serial.println("Data saved.");
    
    // print to the serial port too:
    
//  Serial.print(now.year(), DEC);
//   Serial.print('-');
 //   Serial.print(now.month(), DEC);
  //  Serial.print('-');
 //   Serial.print(now.day(), DEC);
//    Serial.print(' ');
 //   Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
 //    Serial.print(',');
    //Serial.print(bmp.readTemperature());
  //  Serial.print(",");
    //Serial.print(bmp.readPressure());
    // Serial.print(",");
    //Serial.print((float)DHT11.humidity);
     // Serial.print(",");
    //Serial.print((float)DHT11.temperature);
     // Serial.print(",");
     // Serial.print(dewPointFast(DHT11.temperature, DHT11.humidity));
  //   Serial.println(LDRReading);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
   
  }
 
 {
 
   if (client.connect(server, 89)) {

     Serial.println("Data Sent to server.");
    client.print("GET http://dev.futuragora.pt:89/sensorcentral/fasensor1/add.php?");
    client.print("temperature=");    
    client.print(bmp.readTemperature());
    client.print("&&");
    client.print("pressure=");
    client.print(bmp.readPressure());
    client.print("&&");
   client.print("humidity=");
   client.print((float)DHT11.humidity, 2);
     client.print("&&");
   client.print("temperature2=");
   client.print((float)DHT11.temperature, 2);
        client.print("&&");
   client.print("dew=");
   client.print(dewPointFast(DHT11.temperature, DHT11.humidity));
    client.println();
    client.println();
    
// disconnecting from server
 //   Serial.println("disconnecting. send");
    client.stop();
 } 
 } 
 
  
   delay(15000);
}

