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

 


int Ana0 = A0;
int Ana1 = A1;
int Ana2 = A2;
int Ana3 = A3;
int Ana4 = A4;


// On the Ethernet Shield, CS is pin 4. Note that even if it's not
const int chipSelect = 4;




void setup()
{
  Serial.begin(9600);
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
  
  Serial.println("Card initialized.");
}



void loop()
{
     
int sensorValue = analogRead(A4);
float voltage= sensorValue * (5.0 /1023.0);
 
   if (client.connect(server, 89)) {
    Serial.println("Data Sent to server.");
    client.print("GET http://dev.futuragora.pt/open-senses/ccbs/dbwrite.php?");
    client.print("A0=");    
   client.print(analogRead(Ana0));
       client.print("&&");
        client.print("A1=");
       client.print(analogRead(Ana1));
            client.print("&&");
        client.print("A2=");
        client.print(analogRead(Ana2));
            client.print("&&");
        client.print("A3=");
       client.print(analogRead(Ana3));
            client.print("&&");
        client.print("A4=");
        client.print(voltage);;
    client.println();
    client.println();
    client.stop();
 } 
    delay(59500);
}

