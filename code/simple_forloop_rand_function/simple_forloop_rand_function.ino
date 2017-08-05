
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
int PIN = 2;

// How many NeoPixels are attached to the Arduino?
int NUMPIXELS = 28;


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
// call the function
colorFunctionArg(255,0,0,100);

colorFunctionArg(0,255,0,100);

colorFunctionArg(0,0,255,100);
}

//a function with no arguments
void colorFunctionArg(int r, int g, int b, int del){
  for(int i=0;i<NUMPIXELS;i++){
    //pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(del); // Delay for a period of time (in milliseconds).
  }
}

