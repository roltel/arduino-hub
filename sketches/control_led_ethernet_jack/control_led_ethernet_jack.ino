/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>

int led = 3;
String POST = "";
String SET = "";

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  pinMode(led, OUTPUT);
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  digitalWrite(led, HIGH);
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // it is after the double cr-lf that the variables are
          // read another line!
          String POST = "";
          while(client.available())
          {
            c = client.read();
            // save the variables somewhere
            POST += c;
          }
          if(POST != "")
          {
            if(POST == "led=1"){
              SET = "on";
              Serial.println("on");
            }else{
              SET = "off";
              Serial.println("off");
            }
          }
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connnection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><head><title>Jack's Arudino</title>");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
          client.println("<link href='http://fonts.googleapis.com/css?family=Fjord+One' rel='stylesheet' type='text/css'>");
          client.println("<style>*{font-family:'Fjord One';}body{background-color:#f2f2f2;}h1{color:#222;}</style>");
          client.println("</head><body><h1>Control Jack's LED</h1>");
          client.print("<form method='post'>");
          client.print("<input type=\"radio\" name=\"led\" value=\"0\" onclick=\"this.form.submit()\"");
         
          if(SET != "on"){
           client.print(" checked");
          }
         
          client.print(">Off<br />");
          client.print("<input type=\"radio\" name=\"led\" value=\"1\" onclick=\"this.form.submit()\"");
         
          if(SET == "on"){
           client.print(" checked");
          }
         
          client.print(">On<br />");
          client.print("</form>");
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
 
  if(SET == "on"){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
