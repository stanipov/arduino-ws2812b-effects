#define numLeds NUM_LEDS

void rainbow(CRGB *arr, uint8_t start_hue, uint16_t delay_ms){
  	fill_rainbow (arr, numLeds, start_hue);
    arr = applyGamma_video(arr, 1.8);
    FastLED.show();
    delay(delay_ms);
}


void rainbow_circular(CRGB *arr, uint8_t start_hue, uint16_t delay_ms){
  	fill_rainbow_circular (arr, numLeds, start_hue);
    arr = applyGamma_video(arr, 1.8);
    FastLED.show();
    delay(delay_ms);
}