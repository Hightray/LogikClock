void processButtonSetHours() {
  RTC.readTime();

  int previousHour = RTC.h;
  int newHour = previousHour + 1;

  if (newHour > 12) {
    newHour = 1;
  }

  int previousHourSetPoint = HOUR_SET_POINTS[previousHour];
  int newHourSetPoint = HOUR_SET_POINTS[newHour];

  lastHourSample = newHour;
  lastHourSetPoint = newHourSetPoint;

  RTC.h = newHour;
  RTC.s = 0;
  RTC.writeTime();

  Serial.print("Set Hour To:");
  Serial.println(RTC.h);

  smoothGauge(PIN_HOUR_GAUGE, previousHourSetPoint, newHourSetPoint);
}

void processButtonSetMinutes() {
  RTC.readTime();

  int previousMinute = RTC.m;
  int newMinute = previousMinute + 1;

  if (newMinute > 59) {
    newMinute = 0;
  }

  lastMinuteSample = newMinute;

  RTC.m = newMinute;
  RTC.s = 0;
  RTC.writeTime();

  Serial.print("Set Minute To:");
  Serial.println(RTC.m);

  smoothGauge(PIN_MINUTE_GAUGE,
              map(previousMinute, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX),
              map(newMinute, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX));
}

void processButtonSetColor() {
  unsigned int newRunColor = runColor + 1;

  if (newRunColor > COLOR_COUNT - 1) {
    newRunColor = 1;
  }

  runColor = newRunColor;
  setRGBLEDs(COLORS[newRunColor]);

}
