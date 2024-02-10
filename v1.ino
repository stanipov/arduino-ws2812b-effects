// https://github.com/FastLED/FastLED/wiki/RGBSet-Reference
// https://forum.makerforums.info/t/i-a-looking-for-an-example-of-crgb-array-how-would-i-define-a/64587/2

// Allow interruptions for working controls (e.g. keys or IR remote)
#define FASTLED_ALLOW_INTERRUPTS 1
#include <FastLED.h>

// Strip/string parameters
#define LED_PIN        2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812
#define NUM_LEDS       39
#define DEF_BRIGHTNESS 255

// frame buffer
CRGB leds[NUM_LEDS];
//CRGBArray<NUM_LEDS> leds;

// palettes
#include "palettes.hpp"

// *********** ANIMATION VARIABLES ***********
// common parameters
uint16_t delay_ms = 25; // delay in ms for drawing animations (can be different for different animations)
TProgmemRGBPalette16 *currentPalette = Palette[3]; // default palette, "fire" as of now
float gammaCorr=2.2; 

// fire
uint16_t x, y = 0;
uint8_t scale = 30;  // default: 64
uint8_t speed = 32;  // default: 92
uint8_t blend_alpha = 92; // blending parameter

// twinkle
// Overall twinkle speed.
// 0 (VERY slow) to 8 (VERY fast).  
// 4, 5, and 6 are recommended, default is 4.
#define TWINKLE_SPEED 4

// Overall twinkle density.
// 0 (NONE lit) to 8 (ALL lit at once).  
// Default is 5.
#define TWINKLE_DENSITY 2

// If AUTO_SELECT_BACKGROUND_COLOR is set to 1,
// then for any palette where the first two entries 
// are the same, a dimmed version of that color will
// automatically be used as the background color.
#define AUTO_SELECT_BACKGROUND_COLOR 0

// Background color for 'unlit' pixels
// Can be set to CRGB::Black if desired.
CRGB gBackgroundColor = CRGB::Black; 

// If COOL_LIKE_INCANDESCENT is set to 1, colors will 
// fade out slighted 'reddened', similar to how
// incandescent bulbs change color as they get dim down.
#define COOL_LIKE_INCANDESCENT 0

// animation libraries
#include "cylon.hpp"
#include "comet.hpp"
#include "rainbow.hpp"
#include "fire_1d.hpp"
#include "twinkle.hpp"

// define PWM pin
#define pwmPin1 5

// setting-up
void setup_PWM(uint16_t pwm_freq){
  // Configure Timer1 for custom PWM frequency without a prescaler
  // ChatGPT, Thank you!

  TCCR1A = 0; // Clear TCCR1A register
  TCCR1B = 0; // Clear TCCR1B register
  TCNT1 = 0;  // Initialize counter value to 0

  // Set PWM mode (8-bit phase correct PWM)
  TCCR1A |= (1 << WGM10);

  // Set prescaler to 1 (No prescaling)
  TCCR1B |= (1 << CS10);

  // Enable PWM output on pins 6 and 9
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

  // Calculate new OCR1A value for the given frequency without a prescaler
  OCR1A = (16000000 / (2 * pwm_freq)) - 1;
}

void setup_leds(LEDColorCorrection corr){
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);  
  FastLED.setCorrection(corr);
  FastLED.setBrightness(DEF_BRIGHTNESS);
  FastLED.clear(true);
}

void setup() {
  // LED setup
  // Color corrections 
  // TypicalLEDStrip  TypicalSMD5050 TypicalPixelString
  // TypicalSMD5050=0xFFB0F0 /* 255, 176, 240 */,
  // TypicalLEDStrip=0xFFB0F0 /* 255, 176, 240 */,
  // Typical8mmPixel=0xFFE08C /* 255, 224, 140 */,
  // TypicalPixelString=0xFFE08C /* 255, 224, 140 */,
  setup_leds(TypicalPixelString);

  // random seed
  randomSeed(analogRead(0));

  // set random variables for fire animation
  x = random16();
  y = random16();

  // PWM @ 8 kHz
  setup_PWM(8000);
  pinMode(pwmPin1, OUTPUT);
  
}

// Function to set PWM duty cycle on a specific pin
void setPWMDutyCycle(int pin, int dutyCycle) {
  // Ensure dutyCycle is within valid range (0 to 100)
  dutyCycle = constrain(dutyCycle, 0, 100);

  // Calculate the corresponding PWM value for the given duty cycle
  int pwmValue = map(dutyCycle, 0, 100, 0, 255);

  // Set the PWM value based on the pin
  analogWrite(pin, pwmValue);
}


void two_dots(CRGBSet& L){
  for(int i = 0; i < NUM_LEDS-1; i++) { L(i,i+1) = CRGB::Red; FastLED.delay(33); L(i,i+1) = CRGB::Black; }
}





void loop() {

  //two_dots(leds);
  //DrawComet_Pal(currentPalette, leds);

  //cylon(false, 25);
  //DrawComet();
  //FastLED.show();

  //for (uint8_t i=0; i<10; i++){
  //  setPWMDutyCycle(pwmPin1, i*10);
  //  delay(10*(1+random8(32)));
  //}
  
  // some random PWM
  //setPWMDutyCycle(pwmPin1, (1+random8(100)));
  //delay(25 + random8(100));
  //delay();
  //uint8_t pwm_val = inoise8(scale-y);
  //pwm_val = map(0, 255, 0, 100, pwm_val);
  //setPWMDutyCycle(pwmPin1, pwm_val);

  // Check drawing a comet with a palette
  //currentPalette = Palette[9];
  //DrawComet_Pal(currentPalette);
  //FastLED.show();

  // test rainbow
  //static uint8_t shue = 0;
  //rainbow(leds, shue, delay_ms);
  //shue+=5;

  // Check fire 1d
  //currentPalette = Palette[16];
  //fire1d(leds, *currentPalette, x, y, scale, speed, blend_alpha, delay_ms);
  //x += speed/8;
  //y += speed;

  // Test Twinkle
  currentPalette = Palette[15];
  drawTwinkles(leds, *currentPalette);
  //FastLED.show();
}