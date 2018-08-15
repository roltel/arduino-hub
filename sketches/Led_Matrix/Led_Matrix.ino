#include <font_5x4.h>
#include <HT1632.h>
#include <images.h>
// http://playground.arduino.cc/Main/HT1632C
int i = 0;
int wd;

void setup () {
  // Setup and begin the matrix
  // HT1632.begin(CS1,WR,DATA)
  HT1632.begin( 9, 10, 11);
  
  // Give the width, in columns, of the assigned string
  // FONT_5x4_WIDTH and FONT_5x4_HEIGHT are parameter specified in the "font_5x4.h" file
  wd = HT1632.getTextWidth("HOJE VAI CHOVER", FONT_5X4_WIDTH, FONT_5X4_HEIGHT);
}

void loop () {
  
  // Font rendering example
  HT1632.drawTarget(BUFFER_BOARD(1));
  HT1632.clear();
  HT1632.drawText("41R IS THE BEST", 2*OUT_SIZE - i, 2, FONT_5X4, FONT_5X4_WIDTH, FONT_5X4_HEIGHT, FONT_5X4_STEP_GLYPH);
  HT1632.render();  
  
  i = (i+1)%(wd + OUT_SIZE * 2);  
  delay(50);
}

