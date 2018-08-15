#include <IRremote.h>

int RECV_PIN = 9;
int OUTPUT_PIN = 2;
int OUTPUT_PIN2 = 7;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(OUTPUT_PIN2, OUTPUT);
  pinMode(13, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

int on = 0;
unsigned long last = millis();

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 16756815) { // TIVO button
      // If it's been at least 1/4 second since the last
      // IR received, toggle the relay
      if (millis() - last > 250) {
        on = !on;
        digitalWrite(OUTPUT_PIN, on ? HIGH : LOW);
      }
      
      last = millis();
    }  
     if (results.value == 16754775) { // TIVO button
      // If it's been at least 1/4 second since the last
      // IR received, toggle the relay
      if (millis() - last > 250) {
        on = !on;
        digitalWrite(OUTPUT_PIN2, on ? HIGH : LOW);
      }
      
      last = millis();
    } 
   
   
    
    irrecv.resume(); // Receive the next value
  }
}

