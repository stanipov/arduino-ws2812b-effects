/*
Taken from https://github.com/davepl/DavesGarageLEDSeries/blob/master/LED%20Episode%2006/src/comet.h
*/
#define FASTLED_INTERNAL
#include <FastLED.h>

void DrawComet(CRGB *L)
{
    const byte fadeAmt = 128;
    const int cometSize = 4;
    const int deltaHue  = 4;

    float comet_speed = 0.5;

    static byte hue = HUE_RED;
    static int iDirection = 1;
    static float iPos = 0;

    hue += deltaHue;

    iPos += iDirection*comet_speed;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        L[(int)iPos + i].setHue(hue);
    
    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(8) > 4)
            L[j] = L[j].fadeToBlackBy(fadeAmt);  
            
    L = applyGamma_video(L, gammaCorr);
    FastLED.show(); 
    delay(50);
}


void DrawComet_Pal(TProgmemRGBPalette16 *pal, CRGB *L){
    const byte fadeAmt = 128;
    const int cometSize = 4;
    const int deltaCol  = 4;

    float comet_speed = 0.5;

    static byte col = 0;
    static int iDirection = 1;
    static float iPos = 0;

    iPos += iDirection*comet_speed;
    if (iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for (int i = 0; i < cometSize; i++)
        L[(int)iPos + i] = ColorFromPalette(*pal, col, 255);
    
    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(8) > 4)
            L[j] = L[j].fadeToBlackBy(fadeAmt);  

    L = applyGamma_video(L, gammaCorr);
    FastLED.show(); 
    delay(50);

    col += deltaCol;
}