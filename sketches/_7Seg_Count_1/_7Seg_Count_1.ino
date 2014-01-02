 

// Longer, more obvious example for Arduino 7 segment display
// http://www.hacktronics.com/Tutorials/arduino-and-7-segment-led.html
// License: http://www.opensource.org/licenses/mit-license.php (Go crazy)
// Arduino - 7Seg
// 2 - 7
// 3 - 6
// 4 - 4
// 5 - 2
// 6 - 1
// 7 - 9
// 8 - 10

void setup() {              
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, 0);  // start with the "dot" off
}

void loop() {
 // write '9'
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
  delay(100);
  
 // write '8'
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(100);
 
 // write '7'
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(100);
 // write '6'
 digitalWrite(2, 0);
 digitalWrite(3, 1);
 digitalWrite(4, 0);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(100);
 // write '5'
 digitalWrite(2, 0);
 digitalWrite(3, 1);
 digitalWrite(4, 0);
 digitalWrite(5, 0);
 digitalWrite(6, 1);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(100);
 // write '4'
 digitalWrite(2, 1);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 0);
 digitalWrite(8, 0);
 delay(100);
 // write '3'
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 0);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 0);
 delay(100);
 // write '2'
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 digitalWrite(4, 1);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 1);
 digitalWrite(8, 0);
 delay(100);
 // write '1'
 digitalWrite(2, 1);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 1);
 digitalWrite(6, 1);
 digitalWrite(7, 1);
 digitalWrite(8, 1);
 delay(100);
 // write '0'
 digitalWrite(2, 0);
 digitalWrite(3, 0);
 digitalWrite(4, 0);
 digitalWrite(5, 0);
 digitalWrite(6, 0);
 digitalWrite(7, 0);
 digitalWrite(8, 1);
 delay(400);
}
