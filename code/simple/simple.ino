
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

int delayval = 500; // delay for half a second

void setup() {
  // you can set overall brightness
  pixels.setBrightness(100);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
    /*Syntax:
    RGB:      strip.setPixelColor(PIXEL, int r, int g, int b);
    RGBW:     strip.setPixelColor(PIXEL, int r, int g, int b, int w);
    Hex RGB:  strip.setPixelColor(PIXEL, 0xFFFFFF);
    */
    pixels.setPixelColor(0, pixels.Color(0,150,0)); // Moderately bright green color
    //pixels.setPixelColor(0, 0x00FF0000); //set to red
    pixels.show();
    delay(500);
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show();
    delay(500);
        
}
