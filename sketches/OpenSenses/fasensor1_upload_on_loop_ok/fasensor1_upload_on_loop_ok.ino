
#include <SPI.h>
#include <Ethernet.h>

// Sensor testing
int sensorValue = 0;

// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.futuragora.pt";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,1,177);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

int looped = 1;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
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
  if (client.connect(server, 80)) {
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
    if (client.connect(server, 80)) {
 // sendig data to server   
  Serial.println("connected send");
    client.print("GET http://futuragora.pt/arduino/dataupload/add.php?temp1=324");
    client.println();
    client.println();
    
// disconnecting from server
    Serial.println("disconnecting. send");
    client.stop();
 } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  
 { 
   delay(50000000);}
}

