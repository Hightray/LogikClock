void updateTimeGauges() {
  updateTimeGauges(false);
}

void updateTimeGauges(bool resumeActive) {
  RTC.readTime();
  logTime();

  /* Set Hours */
  unsigned int hourSetPoint = HOUR_SET_POINTS[RTC.h];

  if ((hourSetPoint != lastHourSetPoint) || resumeActive) {
    smoothGauge(PIN_HOUR_GAUGE, lastHourSetPoint, hourSetPoint);
    lastHourSample = RTC.h;
    lastHourSetPoint = hourSetPoint;
  }

  /* Set Minutes */
  unsigned int minuteSetPoint = map(RTC.m, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX);
  unsigned int lastMinuteSetPoint = map(lastMinuteSample, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX);

  if ((RTC.m != lastMinuteSample) || resumeActive) {
    smoothGauge(PIN_MINUTE_GAUGE, lastMinuteSetPoint, minuteSetPoint);
    lastMinuteSample = RTC.m;
  }

  /* Set Seconds */
  unsigned int secondSetPoint = map(RTC.s, 0, 59, GAUGE_SECOND_MIN, GAUGE_SECOND_MAX);
  unsigned int lastSecondSetPoint = map(lastSecondSample, 0, 59, GAUGE_SECOND_MIN, GAUGE_SECOND_MAX);

  if ((RTC.s != lastSecondSample) || resumeActive) {
    smoothGauge(PIN_SECOND_GAUGE, lastSecondSetPoint, secondSetPoint);
    lastSecondSample = RTC.s;
  }
}

void logTime() {
  Serial.print(RTC.h);
  Serial.print(":");
  Serial.print(RTC.m);
  Serial.print(":");
  Serial.println(RTC.s);
}
