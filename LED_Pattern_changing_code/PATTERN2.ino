void PATTERN2() {
  // put your main code here, to run repeatedly:
  for (int i = 9; i >= -3 && PATTERN == 2; i--) {
    if (i != -1 && i != -2 && i != -3 && i <= 9) {
      leds2[i] = CRGB ( 0, 255, 0);
      leds3[i] = CRGB ( 0, 255, 0);
      FastLED.show();
    }
    if (i != -1 && i != -2 && i <= 8) {
      leds2[i + 1] = CRGB ( 0, 255, 0);
      leds3[i + 1] = CRGB ( 0, 255, 0);
      FastLED.show();
    }
    if (i != -1 && i <= 7) {
      leds2[i + 2] = CRGB ( 0, 255, 0);
      leds3[i + 2] = CRGB ( 0, 255, 0);
      FastLED.show();
    }
    if (i <= 6) {
      FIXED();
      leds2[i + 3] = CRGB ( 0, 0, 0);
      leds3[i + 3] = CRGB ( 0, 0, 0);
      FastLED.show();
    }
    delay(50);
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      delay(500);
      for (int j = 0; j <= 9; j++) {
        leds2[j] = CRGB ( 0, 0, 0);
        leds3[j] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
  for (int i = 9; i >= -3 && PATTERN == 2; i--) {
    if (i != -1 && i != -2 && i != -3 && i <= 9) {
      leds2[i] = CRGB ( 255, 0, 0);
      leds3[i] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
    if (i != -1 && i != -2 && i <= 8) {
      leds2[i + 1] = CRGB ( 255, 0, 0);
      leds3[i + 1] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
    if (i != -1 && i <= 7) {
      leds2[i + 2] = CRGB ( 255, 0, 0);
      leds3[i + 2] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
    if (i <= 6) {
      FIXED();
      leds2[i + 3] = CRGB ( 0, 0, 0);
      leds3[i + 3] = CRGB ( 0, 0, 0);
      FastLED.show();
    }
    delay(50);
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      delay(500);
      for (int j = 0; j <= 9; j++) {
        leds2[j] = CRGB ( 0, 0, 0);
        leds3[j] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
  for (int i = 9; i >= -3 && PATTERN == 2; i--) {
    if (i != -1 && i != -2 && i != -3 && i <= 9) {
      leds2[i] = CRGB ( 0, 0, 255);
      leds3[i] = CRGB ( 0, 0, 255);
      FastLED.show();
    }
    if (i != -1 && i != -2 && i <= 8) {
      leds2[i + 1] = CRGB ( 0, 0, 255);
      leds3[i + 1] = CRGB ( 0, 0, 255);
      FastLED.show();
    }
    if (i != -1 && i <= 7) {
      leds2[i + 2] = CRGB ( 0, 0, 255);
      leds3[i + 2] = CRGB ( 0, 0, 255);
      FastLED.show();
    }
    if (i <= 6) {
      FIXED();
      leds2[i + 3] = CRGB ( 0, 0, 0);
      leds3[i + 3] = CRGB ( 0, 0, 0);
      FastLED.show();
    }
    delay(50);
    PWM = pulseIn(10, HIGH, 25000); // Read the pulse width of
    if (PWM >= 1900 && PWM <= 2150) {
      PATTERN = PATTERN + 1;
      delay(500);
      for (int j = 0; j <= 9; j++) {
        leds2[j] = CRGB ( 0, 0, 0);
        leds3[j] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
  }
}
