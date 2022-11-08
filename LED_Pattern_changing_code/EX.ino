#include "FastLED.h"

// this is the number of leds per single strip
#define NUM_LEDS 12

// have 2 independent CRGBs

CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
int PATTERN = 0;
int PWM;
void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT);
  FastLED.addLeds<NEOPIXEL, 7>(leds2, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 5>(leds3, NUM_LEDS);
  LEDS.setBrightness(128);
}

void loop() {
  PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
  if (PWM >= 1900 && PWM <= 2150) {
    PATTERN = PATTERN + 1;
    delay(500);
  }
  else if (PWM >= 900 && PWM <= 1500) {
    PATTERN = PATTERN;
  }
  Serial.print("Pattern = ");
  Serial.println(PATTERN);
  if (PATTERN == 1) {
    FIXED();
    PATTERN1();
    Serial.print("Pattern = ");
    Serial.println(PATTERN);
  }
  if (PATTERN == 2) {
    FIXED();
    PATTERN2();
    Serial.print("Pattern = ");
    Serial.println(PATTERN);
  }
  if (PATTERN == 3) {
    FIXED();
    PATTERN3();
    Serial.print("Pattern = ");
    Serial.println(PATTERN);
  }
  if (PATTERN == 4) {
    PATTERN4();
    Serial.print("Pattern = ");
    Serial.println(PATTERN);
  }
  if (PATTERN == 5) {
    PATTERN5();
    Serial.print("Pattern = ");
    Serial.println(PATTERN);
  }
}
