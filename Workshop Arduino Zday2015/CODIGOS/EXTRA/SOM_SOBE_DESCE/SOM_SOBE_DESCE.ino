#include "pitch.h"
int cota = 1, freq = 0;
int som = 13;
void setup() {
  pinMode(som, OUTPUT);

}

void loop() {
  // change the brightness for next time through the loop:
  freq = freq + cota;
  tone(som,freq,100);

  // reverse the direction of the fading at the ends of the fade: 
  if (freq == 0 || freq == 5000) {
    cota = -cota ; 
  }     
}
