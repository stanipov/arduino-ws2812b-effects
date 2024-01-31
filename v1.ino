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

#define pwmPin1 5

// animation libraries
#include "cylon.hpp"
#include "comet.hpp"

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
  // Typical values for 8 mm "pixels on a string".
  // Also for many through-hole 'T' package LEDs.
  // Typical8mmPixel=0xFFE08C /* 255, 224, 140 */,
  // TypicalPixelString=0xFFE08C /* 255, 224, 140 */,
  setup_leds(TypicalPixelString);

  // random seed
  randomSeed(analogRead(0));

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


void loop() {
  //cylon(false, 25);
  //DrawComet();
  //FastLED.show();
  //for (uint8_t i=0; i<10; i++){
  //  setPWMDutyCycle(pwmPin1, i*10);
  //  delay(10*(1+random8(32)));
  //}
  setPWMDutyCycle(pwmPin1, (1+random8(100)));
  delay(25 + random8(100));
  //delay();


}