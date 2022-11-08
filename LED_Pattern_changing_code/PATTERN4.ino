void PATTERN4() {
  // put your main code here, to run repeatedly:
  for (int j = 0; j <= 11 && PATTERN == 4; j++) {
    leds2[j] = CRGB ( 255, 255, 0);
    leds3[j] = CRGB ( 255, 255, 0);
    FastLED.show();
  }
  for (int i = 0; i <= 11 && PATTERN == 4; i++) {
    leds2[i] = CRGB ( 0, 255, 0);
    leds3[i] = CRGB ( 0, 255, 0);
    FastLED.show();
    delay(50);
    leds2[i] = CRGB ( 255, 255, 0);
    leds3[i] = CRGB ( 255, 255, 0);
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      delay(500);
      for (int j = 0; j <= 11; j++) {
        leds2[j] = CRGB ( 0, 0, 0);
        leds3[j] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
  for (int j = 0; j <= 11 && PATTERN == 4; j++) {
    leds2[j] = CRGB ( 255, 0, 255);
    leds3[j] = CRGB ( 255, 0, 255);
    FastLED.show();
  }
  for (int i = 0; i <= 11 && PATTERN == 4; i++) {
    leds2[i] = CRGB ( 0, 0, 255);
    leds3[i] = CRGB ( 0, 0, 255);
    FastLED.show();
    delay(50);
    leds2[i] = CRGB ( 255, 0, 255);
    leds3[i] = CRGB ( 255, 0, 255);
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      delay(500);
      for (int j = 0; j <= 11; j++) {
        leds2[j] = CRGB ( 0, 0, 0);
        leds3[j] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
  for (int j = 0; j <= 11 && PATTERN == 4; j++) {
    leds2[j] = CRGB ( 0, 255, 255);
    leds3[j] = CRGB ( 0, 255, 255);
    FastLED.show();
  }
  for (int i = 0; i <= 11 && PATTERN == 4; i++) {
    leds2[i] = CRGB ( 255, 0, 0);
    leds3[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(50);
    leds2[i] = CRGB ( 0, 255, 255);
    leds3[i] = CRGB ( 0, 255, 255);
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      delay(500);
      for (int j = 0; j <= 11; j++) {
        leds2[j] = CRGB ( 0, 0, 0);
        leds3[j] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
}
