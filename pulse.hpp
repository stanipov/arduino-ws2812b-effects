#include "FastLED.h"
#define numLeds NUM_LEDS

void sinewave(CRGB *arr, uint8_t bpm, uint8_t fadeAmt,  uint8_t hue, uint16_t delay_ms){
  // A sine wave of same color
  // If hue is unchanged, it will be the same color all the time
  fadeToBlackBy(arr, numLeds, fadeAmt);
  uint8_t pos1 = beatsin8(bpm, 0, numLeds-1);
  arr[pos1] += CHSV(hue, 255, 255);
  arr = applyGamma_video(arr, gammaCorr);
  FastLED.show();
  delay(delay_ms);
}

void sinewave_pal(CRGB *arr, TProgmemRGBPalette16 *pal, uint8_t bpm, uint8_t fadeAmt,  uint8_t hue, uint16_t delay_ms){
  // A sine wave of color from a palette
  fadeToBlackBy(arr, numLeds, fadeAmt);
  uint8_t pos1 = beatsin8(bpm, 0, numLeds-1);
  arr[pos1] += ColorFromPalette(*pal, hue, 255);
  arr = applyGamma_video(arr, gammaCorr);
  FastLED.show();
  delay(delay_ms);
}