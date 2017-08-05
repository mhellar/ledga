#include <ESP8266WiFi.h> 
const char* ssid = "ssid"; //wifi ssid / wifi name
const char* password = "pass"; //wifi password
int ledPin = LED_BUILTIN; 

#include <Adafruit_NeoPixel.h>

#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(28, PIN, NEO_GRB + NEO_KHZ800);

  
WiFiServer server(80); 
void setup() { 
   strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 Serial.begin(115200); 
 delay(10); 
 pinMode(ledPin, OUTPUT); 
 digitalWrite(ledPin, LOW); 
 // Connect to WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected"); 
 // Start the server 
 server.begin(); 
 Serial.println("Server started"); 
 // Print the IP address 
 Serial.print("Use this URL to connect: "); 
 Serial.print("http://"); 
 Serial.print(WiFi.localIP()); 
 Serial.println("/"); 
} 
void loop() { 
 // Check if a client has connected 
 WiFiClient client = server.available(); 
 if (!client) { 
   return; 
 } 
 // Wait until the client sends some data 
 Serial.println("new client"); 
 while(!client.available()){ 
   delay(1); 
 } 
 // Read the first line of the request 
 String request = client.readStringUntil('\r'); 
 Serial.println(request); 
 client.flush(); 
 // Match the request 
 int value; 
 if (request.indexOf("/r") != -1)  { 
   value = 1; 
   colorWipe(strip.Color(255, 0, 0), 5); // Red
 } 
 if (request.indexOf("/g") != -1)  { 
   value = 2; 
  colorWipe(strip.Color(0, 255, 0), 5); // Green
 } 
  if (request.indexOf("/b") != -1)  { 
   value = 3; 
    colorWipe(strip.Color(0, 0, 255), 5); // Blue
  }
    if (request.indexOf("/rb") != -1)  { 
   value = 4; 
   rainbow(5);
  } 
unsigned long time= millis();
// Set ledPin according to the request 
//digitalWrite(ledPin, value); 
 // Return the response 
 client.println("HTTP/1.1 200 OK"); 
 client.println("Content-Type: text/html"); 
 client.println(""); //  do not forget this one 
 client.println("<!DOCTYPE HTML>"); 
 client.println("<html>"); 
 client.print("<body style='background: #00979C'>"); 
 client.println("<h1 align ='center'>"); 
 client.println("<font-color='red'>"); 
 client.println("Led Workshop"); 
 client.println("</font>"); 
 client.println("</h1>"); 
 client.println("<bg color ='#00ff00'>"); 
 client.println("</bg>"); 
 client.println("<p align ='center'>"); 
 client.print("Led is Now: "); 
 client.println("</p>"); 
 
 if(value == 1) { 
   client.println("<p align ='center'>"); 
   client.print("Red"); 
   client.println("</p>"); 
 } else if(value == 2) { 
   client.println("<p align ='center'>"); 
   client.print("Green"); 
   client.println("</p>"); 
 } else if(value == 3) { 
   client.println("<p align ='center'>"); 
   client.print("Blue"); 
   client.println("</p>"); 
 } else if(value == 4) { 
   client.println("<p align ='center'>"); 
   client.print("Rainbow"); 
   client.println("</p>"); 
 } 
 
 client.println("<br><br>"); 
 client.println("<p align ='center'>"); 
 client.println("<a  href=\"/r\"\"><button>Red</button></a>"); 
 client.println("<a  href=\"/g\"\"><button>Green</button></a><br />");   
 client.println("<a  href=\"/b\"\"><button>Blue</button></a><br />");  
  client.println("<a  href=\"/rb\"\"><button>Rainbow</button></a>"); 
 client.println("</p>"); 
 client.println("<p>");  
 client.println("</p>"); 
 client.println("</body>"); 
 client.println("</html>"); 
 delay(1); 
 Serial.println("Client disonnected"); 
 Serial.println(""); 
} 

//neopixel functions
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
