#include <FastLED.h>
#define numLeds NUM_LEDS

uint8_t gen_perlin_noise8_2d(int X, int Y){
  /*
  Generates Perlin's noise using noise8()
  */
  static uint8_t noise;
  noise = inoise8 (X, Y);
  // The range of the inoise8 function is roughly 16-238.
  // These two operations expand those values out to roughly 0..255
  noise = qsub8(noise, 16);
  noise = qadd8(noise, scale8(noise, 39));
  return noise;
}

void fire1d(CRGB *arr, TProgmemRGBPalette16 *pal, uint16_t x, uint16_t y, uint8_t scale, uint8_t speed, uint8_t blend_a, uint16_t delay_ms){
  static uint8_t col, bri;
  //static uint32_t t;

  //t += speed;
  for (uint8_t i=0; i<numLeds; i++){
    //col = gen_perlin_noise8_2d(x * scale, (y * scale) - t), 0);
    col = gen_perlin_noise8_2d(i * scale, (i * scale) - y);
    bri = col;

    if (bri > 127){
      bri = 255;
    }
    else {
      bri = bri * 2;
    }

    nblend(arr[i], ColorFromPalette(*pal, col, bri), blend_a); //speed
  }
  arr = applyGamma_video(arr, 1.8);
  FastLED.show();
  delay(delay_ms);
}





