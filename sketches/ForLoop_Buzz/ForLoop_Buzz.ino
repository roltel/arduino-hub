#include <SPI.h>

/*
  For Loop Iteration
 
 Demonstrates the use of a for() loop.
 Lights multiple LEDs in sequence, then in reverse.
 
 The circuit:
 * LEDs from pins 2 through 7 to ground
 
 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/ForLoop
 */

int timer = 200;           // The higher the number, the slower the timing.

void setup() {
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 2; thisPin < 8; thisPin++)  {
    pinMode(thisPin, OUTPUT);      
  }

  // declare pin 9 to be an output:
  pinMode(11, OUTPUT);
  beep(500);
  beep(50);
  beep(50);
  delay(200);
} 

void loop() {
  // loop from the lowest pin to the highest:
  for (int thisPin = 2; thisPin < 8; thisPin++) {
    // turn the pin on:
    digitalWrite(thisPin, HIGH);  
    delay(timer);                  
    // turn the pin off:
    digitalWrite(thisPin, LOW);    
  }

  // loop from the highest pin to the lowest:
  for (int thisPin = 7; thisPin >= 2; thisPin--) {
    // turn the pin on:
    digitalWrite(thisPin, HIGH);
    delay(timer);
    // turn the pin off:
    digitalWrite(thisPin, LOW);

}  beep(1000); 
}

void beep(unsigned char delayms){
  analogWrite(11, 200);      // Almost any value can be used except 0 and 255
                           // experiment to get the best tone
  delay(delayms);          // wait for a delayms ms
  analogWrite(11, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}  
