#include <TinkerKit.h>

/* 
 * Relay Box
 * 
 * Digital Pin Wiring:  
 *         pin 12 - Relay Pin 
 *         pin 13 - LED Pin 
 * 
 * License: This work is licenced under the Creative Commons  
 *          Attribution-Share Alike 3.0 Unported License. To  
 *          view a copy of this licence, visit  
 *          http://creativecommons.org/licenses/by-sa/3.0/  
 *          or send a letter to Creative Commons, 171 Second  
 *          Street, Suite 300, San Francisco, California 94105,  
 *          USA.
 */  

//--- Digital Pins
int ledPin = 13;
TKRelay relay(O0);

void setup()
{   
	//--- Set up the LEDs as outputs   
	pinMode(ledPin, OUTPUT);     

	//--- open the serial port  
	Serial.begin(9600);
}

void loop()
{   
  	digitalWrite(ledPin, HIGH);   // set the LED pin High   
	 relay.on(); // set the relay pin High   
	delay(10000);                 // wait for a second   
	digitalWrite(ledPin, LOW);    // set the LED pin High   
	relay.off(); // set the relay pin High   
	delay(2500);    
  

}
