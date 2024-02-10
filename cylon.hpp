#include <FastLED.h>
#define numLeds NUM_LEDS

void fadeall(CRGB *L) { 
  for(int i = 0; i < numLeds; i++) { 
      L[i].nscale8(250); 
    } 
}

void cylon(CRGB *L, bool double_pass, uint8_t ms_delay){ 
  // Cylon animation from FastLED examples
  static uint8_t hue = 0;
  for(int i = 0; i < numLeds; i++) {
		// Set the i'th led to red 
		L[i] = CHSV(hue++, 255, 255);
		// Show the leds
    L = applyGamma_video(L, gammaCorr);
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		//leds[i] = CRGB::Black;
		fadeall(L);
    //FastLED.show(); 
		// Wait a little bit before we loop around and do it again
		delay(ms_delay);
	}

	// Now go in the other direction.  
  if (double_pass){
    for(int i = (numLeds)-1; i >= 0; i--) {
      // Set the i'th led to red 
      L[i] = CHSV(hue++, 255, 255);
      // Show the leds
      L = applyGamma_video(L, gammaCorr);
      FastLED.show();
      // now that we've shown the leds, reset the i'th led to black
      //leds[i] = CRGB::Black;
      fadeall(L);
      //FastLED.show(); 
      // Wait a little bit before we loop around and do it again
      delay(ms_delay);
    }
  }
}