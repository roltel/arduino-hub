/*
  SD card datalogger
 
 This example shows how to log data from three analog sensors 
 to an SD card using the SD library.
 	
 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 	 
 */
 #include <SPI.h>
#include <Ethernet.h>


// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "dev.futuragora.pt";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,177);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

 
#include <Adafruit_BMP085.h>
#include <SD.h>
#include <Wire.h>

Adafruit_BMP085 bmp;


// 
//   FILE:  dht11_test1.pde
// PURPOSE: DHT11 library test sketch for Arduino
//

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}

// fast integer version with rounding
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


#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 6



// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

void setup()
{
 // Open serial communications and wait for port to open:
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
  
  // fim de parte enviar

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}



void loop()
{
  
  
  // make a string for assembling the data to log:
//  String dataString = "";

 int chk = DHT11.read(DHT11PIN);


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(bmp.readTemperature());
    dataFile.print(",");    
    dataFile.print(bmp.readPressure());
     dataFile.print(",");    
    dataFile.print(DHT11.humidity);
     dataFile.print(",");    
    dataFile.print(DHT11.temperature);
      dataFile.print(",");    
    dataFile.println(dewPointFast(DHT11.temperature, DHT11.humidity));
    dataFile.close();
    
    
    // print to the serial port too:
    Serial.print(bmp.readTemperature());
    Serial.print(",");
    Serial.print(bmp.readPressure());
     Serial.print(",");
    Serial.print((float)DHT11.humidity);
      Serial.print(",");
    Serial.print((float)DHT11.temperature);
     Serial.print(",");
     Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    delay(5000);
  }
 


 {
 
   if (client.connect(server, 89)) {
      
     
      
 // sendig data to server   
 // Serial.println("connected send");
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
 
  
   delay(5000);
}











