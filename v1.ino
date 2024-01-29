// Allow interruptions for working controls (e.g. keys or IR remote)
#define FASTLED_ALLOW_INTERRUPTS 1
#include <FastLED.h>

// Strip/string parameters
#define LED_PIN        2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812
#define NUM_LEDS       39
#define DEF_BRIGHTNESS 127

// frame buffer
CRGB leds[NUM_LEDS];

// animation libraries
#include "cylon.hpp"
#include "comet.hpp"

// setting-up
void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);  
  // Color corrections 
  // TypicalLEDStrip  TypicalSMD5050 TypicalPixelString
  // TypicalSMD5050=0xFFB0F0 /* 255, 176, 240 */,
  // TypicalLEDStrip=0xFFB0F0 /* 255, 176, 240 */,
  // Typical values for 8 mm "pixels on a string".
  // Also for many through-hole 'T' package LEDs.
  // Typical8mmPixel=0xFFE08C /* 255, 224, 140 */,
  // TypicalPixelString=0xFFE08C /* 255, 224, 140 */,
  FastLED.setCorrection(TypicalPixelString);
  FastLED.setBrightness(DEF_BRIGHTNESS);

  // random seed
  randomSeed(analogRead(0));
}


void loop() {
  //cylon(false, 25);
  DrawComet();
  FastLED.show();
}