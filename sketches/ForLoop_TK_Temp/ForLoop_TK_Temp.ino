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
 #include <TinkerKit.h>

TKThermistor therm(I0);       // creating the object 'therm' that belongs to the 'TKThermistor' class 
                              // and giving the value to the desired output pin

float C, F;		      // temperature readings are returned in float format


int timer = 200;           // The higher the number, the slower the timing.

void setup() {
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 2; thisPin < 8; thisPin++)  {
    pinMode(thisPin, OUTPUT);      
  }
  {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}
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
  }
  {
  C = therm.getCelsius();     	// Reading the temperature in Celsius degrees and store in the C variable
  F = therm.getFahrenheit();  	// Reading the temperature in Fahrenheit degrees and store in the F variable

  // Print the collected data in a row on the Serial Monitor
  Serial.print("Analog reading: \t");	// Reading the analog value from the thermistor
  Serial.print(therm.get());
  Serial.print("\tC: \t");
  Serial.print(C);
  Serial.print("\tF: \t");
  Serial.println(F);

  delay(1000);                // Wait one second before get another temperature reading
}
}

