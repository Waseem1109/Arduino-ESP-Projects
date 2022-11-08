void PATTERN5() {
  static int n = 0;
  for (float j = 0; j <= 255 && PATTERN == 5; j = j + 42.5) {
    for (int i = 0; i <= 11; i++) {
      if (i == n) {
        leds2[i] = CRGB ( 255, 0, 0);
        leds3[i] = CRGB ( 255, 0, 0);
        FastLED.show();
      }
      else {
        leds2[i] = CRGB ( 0, j, j);
        leds3[i] = CRGB ( 0, j, j);
        FastLED.show();
      }
    }
    n = n + 1;
    Serial.print("n = ");
    Serial.println(n);
    delay(50);
    if (n > 11) {
      n = 0;
    }
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      if (PATTERN > 5) {
        PATTERN = 1;
      }
      delay(500);
      for (int k = 0; k <= 11; k++) {
        leds2[k] = CRGB ( 0, 0, 0);
        leds3[k] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
  for (float j = 255; j >= 0 && PATTERN == 5; j = j - 42.5) {
    for (int i = 0; i <= 11; i++) {
      if (i == n) {
        leds2[i] = CRGB ( 255, 0, 0);
        leds3[i] = CRGB ( 255, 0, 0);
        FastLED.show();
      }
      else {
        leds2[i] = CRGB ( 0, j, j);
        leds3[i] = CRGB ( 0, j, j);
        FastLED.show();
      }
    }
    n = n + 1;
    Serial.print("n = ");
    Serial.println(n);
    delay(50);
    if (n > 11) {
      n = 0;
    }
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      if (PATTERN > 5) {
        PATTERN = 1;
      }
      delay(500);
      for (int k = 0; k <= 11; k++) {
        leds2[k] = CRGB ( 0, 0, 0);
        leds3[k] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
}
