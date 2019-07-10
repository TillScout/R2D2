/*
FLD lighting

This sketch is meant to light the Front Logic Displays
Author: Till Barmeier
Email: tbarmeier@googlemail.com

Part of this code is taken from the FLD implementation of Joymonkey (https://github.com/joymonkey/logicengine). 
Also the general logic behind the color change mechanism is not my inception, but from Joymonkey.



 */


////////////// LIBRARIES /////////////
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

///////////// PIN AND VARIABLE DEFINITIONS //////////////////
#define FLD_TOP_PIN 6
#define FLD_BOT_PIN 5
#define BRIGHTNESS 30

uint32_t blue;
uint32_t white;
uint32_t black;

///////////// CREATION OF LED OBJECTS ////////////////

Adafruit_NeoMatrix FLD_TOP = Adafruit_NeoMatrix(8, 5, FLD_TOP_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRBW  + NEO_KHZ800);

Adafruit_NeoMatrix FLD_BOT = Adafruit_NeoMatrix(8, 5, FLD_BOT_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRBW  + NEO_KHZ800);

uint32_t Color(int r, int g, int b, int w){
  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}


////////////// HELPER FUNCTIONS FOR STARTUP SEQUENCE //////////////////

void light_line(Adafruit_NeoMatrix &matrix, int line, uint32_t color, boolean update){
  int width = matrix.width();
  for (int i=0; i < width; i++){
    matrix.setPixelColor(width*line+i, color);
  }
  if(update){
    matrix.show();
  }
} // assign a given color to an indiviual line, update the matrix (i.e. actually light it up) only when true


void light_row(Adafruit_NeoMatrix &matrix, int row, uint32_t color, boolean update){
  int width = matrix.width();
  for (int i=0; i < matrix.height(); i++){
    matrix.setPixelColor(i*width+row, color);
  }
  if(update){
    matrix.show();
  }
} // assign a given color to an indiviual line, update the matrix (i.e. actually light it up) only when true

void scan_line(Adafruit_NeoMatrix &matrix, uint32_t color){
  for (int i = 0; i <= matrix.height()-1; i++){
    light_line(matrix, i-1, black, false);
    light_line(matrix,i,color,true);
    delay(50);
  }
  for (int i = matrix.height()-2; i >=0; i--){
    light_line(matrix, i+1, black, false);
    light_line(matrix,i,color,true);
    delay(50);
  }
  light_line(matrix, 0, black, true);
} // show a scanning animation along the lines of the matrix

void scan_row(Adafruit_NeoMatrix &matrix, uint32_t color){
  for (int i = 0; i <= matrix.width()-1; i++){
    light_row(matrix, i-1, black, false);
    light_row(matrix,i,color,true);
    delay(50);
  }
  for (int i = matrix.width()-2; i >=0; i--){
    light_row(matrix, i+1, black, false);
    light_row(matrix,i,color,true);
    delay(50);
  }
  light_row(matrix,0, black, true);
} // show a scanning animation along the rows of the matrix

void startup(Adafruit_NeoMatrix &matrix){
  scan_line(matrix, blue);
  scan_row(matrix, blue);
  scan_line(matrix, white);
  scan_row(matrix, white);
  } // create a startup animation for the FLD as a general "sanity check"
  


void setup(){
  FLD_TOP.begin();
  FLD_BOT.begin();
  FLD_TOP.setBrightness(BRIGHTNESS);
  FLD_BOT.setBrightness(BRIGHTNESS);
  FLD_TOP.show();
  blue = Color(0,0,255,0);
  white = Color(0,0,0,66);
  black = Color(0,0,0,0);
  startup(FLD_TOP);
  //light_row(FLD_TOP,2,blue,true);
}
  
void loop(){
  //light_line(FLD_TOP, 1, white);
  
}
