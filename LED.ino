void initializeLEDs() {
  setRGBLEDs(COLORS[COLOR_RED]);
  delay(500);
  setRGBLEDs(COLORS[COLOR_GREEN]);
  delay(500);
  setRGBLEDs(COLORS[COLOR_BLUE]);
  delay(500);
  ledAnimation(LED_ANIMATION_BLINK, runColor, 100, 3);
  setRGBLEDs(runColor);
}

void ledAnimation(int animation, int color[], int delayValue, int timesToRepeat) {
  for (int i = 0; i < timesToRepeat; i++) {
    switch (animation) {
      case LED_ANIMATION_BLINK:
        setRGBLEDs(color);
        delay(delayValue);
        setRGBLEDs(COLORS[COLOR_BLACK]);
        delay(delayValue);
        break;
      case LED_ANIMATION_RANDOM:
        randomSeed(analogRead(0));  // If pin0 is unconnected, pin noise will seed the generator.
        for (int i = 0; i < 8; i++) {
          int rcolor[] = {random(0, 255), random(0, 50), random(0, 50)};
          setRGBLEDs(rcolor);
          delay(delayValue);
        }
        break;
    }
  }
}

void setRGBLEDs(int color[]) {
  analogWrite(PIN_LED_RED, color[LED_RED]);
  analogWrite(PIN_LED_GREEN, color[LED_GREEN]);
  analogWrite(PIN_LED_BLUE, color[LED_BLUE]);
}
