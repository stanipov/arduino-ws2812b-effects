/*
Taken from https://github.com/davepl/DavesGarageLEDSeries/blob/master/LED%20Episode%2006/src/comet.h
*/

void DrawComet()
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
        leds[(int)iPos + i].setHue(hue);
    
    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS; j++)
        if (random(8) > 4)
            leds[j] = leds[j].fadeToBlackBy(fadeAmt);  

    delay(50);
}