#include <Adafruit_Sensor.h>

//Fasensor2
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#define DHTPIN A1// what digital pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
#include <SPI.h>
#include <Ethernet.h>
// Enter a MAC address for your controller below.
byte mac[] = { 0xFE, 0xCD, 0xCE, 0xEF, 0xCE, 0xED };
//IPAddress server(74,125,232,128);  // numeric IP for1 Google (no DNS)
char server[] = "api.thingspeak.com";  
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,110);
// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
#include <Wire.h>

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  delay(1000);  // give the Ethernet shield a second to initialize:
  Serial.println("connecting...");
  dht.begin();
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("conection test");
    Serial.println("disconnecting.");
    client.stop();
 } 
  else {
    Serial.println("connection failed");  // kf you didn't get a connection to the server:
    
  }
} 
void loop() 
{
float h = dht.readHumidity();
 {
   if (client.connect(server, 80)) {
 // sendig data to server   
 // Serial.println("connected send");
    client.print("GET https://api.thingspeak.com/update?api_key=2VS6E0C86WHV5YSZ&"); 
    client.print("field1=");    
    client.print(bmp.readTemperature());
    client.print("&&");
    client.print("field2=");
    client.print(bmp.readPressure());
    client.print("&&");
    client.print("field3=");
    client.print(dht.readHumidity());
   client.println();
    client.println();
    // disconnecting from server
 //   Serial.println("disconnecting. send");
    client.stop();
 }
 else {
    Serial.println("connection failed"); 
 } 
 }
 {  
   delay(59550); // 1 mn de delay
}
}
