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

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
{
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


void loop()
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
   client.print("&&");
   client.print("light=");
   client.print(LDRReading);
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
 
  {
   delay(14550);
}












