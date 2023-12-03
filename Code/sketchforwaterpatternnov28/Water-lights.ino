//Libraries used
#include <FastLED.h>

// number of leds
#define NUM_LEDS 1
//pin connected to arduino
#define DATA_PIN 2


// An array with all the number of LEDs
CRGB leds[NUM_LEDS];

void setup() { 
  //checking of working
  Serial.begin(9600);
  //FASTLED adds number of lights description of each setting -> <type of light/brand of light, Pin it's set to or just DATA_PIN, Type of color RGB or HSV>(leds = pin, number of leds);
    FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    
}

void loop() { 
  // Turns the LED on, then pause
 // Serial.println("This is working 1");
  leds[0] = CRGB::Blue;
  //.show either specifies the LED on or off
  FastLED.show();
  delay(500);
  //checker
Serial.println("This is working ");
  // Turns the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  //checker
  Serial.println("This is working 2");
}
