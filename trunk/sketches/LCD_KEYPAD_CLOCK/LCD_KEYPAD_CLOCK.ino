// http://dimme.net/arduino-lcd-keypad-shield-clock-application/

#include <LiquidCrystal.h>
#include "LCDKeypad.h"
 
#define DAYS 0
#define HOURS 1
#define MINUTES 2
#define SECONDS 3
 
// The LCD screen
LCDKeypad lcd;
 
// The time model
unsigned int days = 0;
unsigned int hours = 0;
unsigned int minutes = 0;
unsigned int seconds = 0;
unsigned int setting = 0;
 
void setup() {
  // Set up the LCD's number of columns and rows: 
  lcd.begin(16,2);
 
  // Set the cursor at the begining of the first row
  lcd.setCursor(0,0);
 
  // Print a text in the first row
  lcd.print("Setting: Days   ");
}
 
void loop() {
  // Increase the time model by one second
  incTime();
 
  // Print the time on the LCD
  printTime();
 
  // Listen for buttons for 1 second
  buttonListen();
}
 
void buttonListen() {
  // Read the buttons five times in a second
  for (int i = 0; i < 5; i++) {
 
    // Read the buttons value
    int button = lcd.button();
 
    switch (button) {
 
    // Right button was pushed
    case KEYPAD_RIGHT:
      setting++;
      break;
 
    // Left button was pushed
    case KEYPAD_LEFT:
      setting--;
      break;
 
    // Up button was pushed
    case KEYPAD_UP:
      switch (setting) {
      case DAYS:
        days++;
        break;
      case HOURS:
        hours++;
        break;
      case MINUTES:
        minutes++;
        break;
      case SECONDS:
        seconds++;
      }     
      break;
 
    // Down button was pushed
    case KEYPAD_DOWN:
      switch (setting) {
      case DAYS:
        days--;
        if (days == -1) days = 99;
        break;
      case HOURS:
        hours--;
        if (hours == -1) hours = 23;
        break;
      case MINUTES:
        minutes--;
        if (minutes == -1) minutes = 59;
        break;
      case SECONDS:
        seconds--;
        if (seconds == -1) seconds = 59;
      }
    }
 
    setting %= 4;
    printSetting();
 
    days %= 100;
    hours %= 24;
    minutes %= 60;
    seconds %= 60;
    printTime();
 
    // Wait one fifth of a second to complete
    while(millis() % 200 != 0);
  }
}
 
// Print the current setting
void printSetting() {
  lcd.setCursor(9,0);
 
  switch (setting) {
  case DAYS:
    lcd.print("Days   ");
    break;  
  case HOURS:
    lcd.print("Hours  ");
    break;
  case MINUTES:
    lcd.print("Minutes");
    break;
  case SECONDS:
    lcd.print("Seconds");
  }
}
 
// Increase the time model by one second
void incTime() {
  // Increase seconds
  seconds++;
 
  if (seconds == 60) {
    // Reset seconds
    seconds = 0;
 
    // Increase minutes
    minutes++;
 
    if (minutes == 60) {
      // Reset minutes
      minutes = 0;
 
      // Increase hours
      hours++;
 
      if (hours == 24) {
        // Reset hours
        hours = 0;
 
        // Increase days
        days++;
      }
    }
  }
}
 
// Print the time on the LCD
void printTime() {
  // Set the cursor at the begining of the second row
  lcd.setCursor(0,1);
  char time[17];
  sprintf(time, "%02i days %02i:%02i:%02i", days, hours, minutes, seconds);
  lcd.print(time);
}
