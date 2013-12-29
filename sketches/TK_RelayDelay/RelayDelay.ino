#include <TinkerKit.h>
 
TKRelay relay(O0);
 
void setup() {
 
}
 
void loop() {
   
  relay.on();
  delay(1000);
  relay.off();
  delay(1000);
   
}
