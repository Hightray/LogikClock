void initializeGauges() {
  /* Do a sweep up and down on the hours gauge. */
  smoothGauge(PIN_HOUR_GAUGE, 0, GAUGE_HOUR_MAX);
  delay(100);
  smoothGauge(PIN_HOUR_GAUGE, GAUGE_HOUR_MAX, 0);
  delay(250);

  /* Do a sweep up and down on the minutes gauge. */
  smoothGauge(PIN_MINUTE_GAUGE, 0, GAUGE_MINUTE_MAX);
  delay(100);
  smoothGauge(PIN_MINUTE_GAUGE, GAUGE_MINUTE_MAX, 0);
  delay(250);

  /* Do a sweep up and down on the seconds gauge. */
  smoothGauge(PIN_SECOND_GAUGE, 0, GAUGE_SECOND_MAX);
  delay(100);
  smoothGauge(PIN_SECOND_GAUGE, GAUGE_SECOND_MAX, 0);
  delay(250);
}

void smoothGauge(int gaugeToSet, int startVal, int endVal) {
  /* Determine the direction the needle is moving. */

  Serial.print("Smooth Gauge: ");
  Serial.print(gaugeToSet);
  Serial.print(", Start: ");
  Serial.print(startVal);
  Serial.print(", End: ");
  Serial.println(endVal);

  int direction = startVal >= endVal ? SMOOTH_GAUGE_DOWN : SMOOTH_GAUGE_UP;

  if (direction == SMOOTH_GAUGE_UP) {
    for (int i = startVal; i <= endVal; i++) {
      delay(SMOOTH_GAUGE_SPEED);
      analogWrite(gaugeToSet, i);
    }
  }

  if (direction == SMOOTH_GAUGE_DOWN) {
    for (int i = startVal; i >= endVal; i--) {
      delay(SMOOTH_GAUGE_SPEED);
      analogWrite(gaugeToSet, i);
    }
  }
}

/*
    Park Gauges is to be used prior to unplugging the clock.  Although things may be OK, I did not like the
    fact that when the power is removed, the needles slam to the bottom of the gauge.  By parking the gauges
    the needles are "smoothgauge"'d to zero and then you can unplug the clock.  When the gauge is parked, the
    program will enter a parked state for 30 seconds.  If the device is not unplugged by then, it will
    go back into active mode.
*/
void parkGauges() {
  unsigned int minuteSetPoint = map(lastMinuteSample, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX);
  unsigned int secondSetPoint = map(lastSecondSample, 0, 59, GAUGE_SECOND_MIN, GAUGE_SECOND_MAX);
  smoothGauge(PIN_HOUR_GAUGE, lastHourSetPoint, 0);
  smoothGauge(PIN_MINUTE_GAUGE, minuteSetPoint, 0);
  smoothGauge(PIN_SECOND_GAUGE, secondSetPoint, 0);

  Serial.println("PARKED");
  delay(GAUGE_PARK_TIME);
  Serial.println("RESUMED");

  /* After 30 seconds, go back to active mode */
  updateTimeGauges(true);
}
