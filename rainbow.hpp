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


void rainbow_gradual_fill(CRGB *arr, uint8_t hue, uint16_t delay_ms){
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


void gradual_fill_fade(CRGB *arr, uint8_t hue, uint16_t delay_ms, uint8_t fadeAmt){
  uint8_t fade_nums = 255 / fadeAmt+1;
  
  for (int i = 0; i < numLeds; i++){
    arr[i].setHue(hue);
    FastLED.show();
    delay(delay_ms);
  }


  for (uint8_t i=0; i<numLeds; i++){
      for (uint8_t c=0; c<=fade_nums; c++){
        arr[i] = CHSV(hue, 255, max(0, 255-fadeAmt*c));
        FastLED.show();
        delay(delay_ms);
        }
      }
}


void gradual_fill_fade2(CRGB *arr, uint8_t hue, uint16_t delay_ms, uint8_t fadeAmt){
  uint8_t fade_nums = 255 / fadeAmt+1;
  uint8_t l ;// = leds[i].getLuma();


  for (int i = 0; i < numLeds; i++){
    arr[i].setHue(hue);
    //arr = applyGamma_video(arr, gammaCorr);
    FastLED.show();
    delay(delay_ms);
  }


  for (uint8_t i=0; i<numLeds; i++){
    l = arr[i].getLuma();
    arr[i] = CHSV(hue, 255, max(0, l-fadeAmt));
    
    //arr[i].fadeToBlackBy(max(0, l-fadeAmt));
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