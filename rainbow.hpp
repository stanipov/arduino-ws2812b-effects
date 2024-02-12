#include "FastLED.h"
#define numLeds NUM_LEDS

void rainbow(CRGB *arr, uint8_t start_hue, uint16_t delay_ms){
  	fill_rainbow (arr, numLeds, start_hue);
    arr = applyGamma_video(arr, gammaCorr);
    FastLED.show();
    delay(delay_ms);
}


void rainbow_circular(CRGB *arr, uint8_t start_hue, uint16_t delay_ms){
  	fill_rainbow_circular (arr, numLeds, start_hue);
    arr = applyGamma_video(arr, gammaCorr);
    FastLED.show();
    delay(delay_ms);
}


void rainbow_step(CRGB *arr, uint8_t start_hue, uint8_t dHue, uint16_t delay_ms){
  static uint8_t hue;

  for (int i = 0; i < numLeds; i++){
    arr[i].setHue(hue);
    hue += dHue;
    delay(delay_ms);
    FastLED.show();
  }

  for (uint8_t i=0; i<numLeds; i++){
    arr[i] = CRGB::Black;
    FastLED.show();
    delay(delay_ms);
  }
}


void gradual_fill(CRGB *arr, uint8_t hue, uint16_t delay_ms){
  for (int i = 0; i < numLeds; i++){
    arr[i].setHue(hue);
    delay(delay_ms);
    FastLED.show();
  }

  for (uint8_t i=0; i<numLeds; i++){
    arr[i] = CRGB::Black;
    FastLED.show();
    delay(delay_ms);
  }

}


void __rainobw_step(CRGB *arr, uint8_t start_hue, uint16_t delay_ms){
  for (uint8_t i=1; i<numLeds; i++){
    fill_rainbow_circular (arr, i, start_hue);
    arr = applyGamma_video(arr, gammaCorr);
    FastLED.show();
    //delay(min(5, delay_ms/5));
    //delay(delay_ms);
  }
  delay(delay_ms);
  FastLED.clear(true);

  /*
  for (uint8_t i=numLeds-1; i>=0; i--){
    arr[i] = CRGB::Black;
    FastLED.show();
    delay(delay_ms);
  }
  */
}