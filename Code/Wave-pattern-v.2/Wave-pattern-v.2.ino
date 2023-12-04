#include <FastLED.h> //Library used https://github.com/FastLED/FastLED
#define NUM_LEDS 60 //number of leds in strip 

CRGBArray<NUM_LEDS> leds;
//                             Type of lED, DATA PIN, Color Type RGB/HSV(number of lights)
void setup() { FastLED.addLeds<WS2812,2, RGB>(leds, NUM_LEDS); }

void loop(){ 
  static uint8_t hue; //sets colour
  for(int i = 0; i < NUM_LEDS; i++) {   //cycles through
    // fade everything out
    leds.fadeToBlackBy(40);

    //sets led value
    leds[i] = CHSV( 240, 255, hue++);
    
    FastLED.delay(50);
  }
}

