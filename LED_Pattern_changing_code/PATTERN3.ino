void PATTERN3() {
  for (int i = 0; i <= 12 && PATTERN == 3; i++) {
    if (i <= 9) {
      leds2[i] = CRGB ( 0, 255, 0);
      leds3[i] = CRGB ( 0, 255, 0);
      FastLED.show();
    }
    if (i != 0 && i <= 10) {
      leds2[i - 1] = CRGB ( 255, 0, 0);
      leds3[i - 1] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
    if (i != 0 && i != 1 && i <= 11) {
      leds2[i - 2] = CRGB ( 0, 0, 255);
      leds3[i - 2] = CRGB ( 0, 0, 255);
      FastLED.show();
    }
    if (i != 0 && i != 1 && i != 2 && i <= 12) {
      leds2[i - 3] = CRGB ( 0, 0, 0);
      leds3[i - 3] = CRGB ( 0, 0, 0);
      FastLED.show();
    }
    delay(50);
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
