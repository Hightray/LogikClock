void processButtonSetHours() {
  // Read current time from RTC
  RTC.readTime();

  // Get the hour value of the RTC
  int previousHour = RTC.h;

  // Increment the hour in response to the user pressing the set hour button
  int newHour = previousHour + 1;

  // 12 Hour clock representation.  If value is over 12, set value to 1.
  if (newHour > 12) {
    newHour = 1;
  }

  // Hour gauge pwm set point value for the previous value of the hour
  int previousHourSetPoint = HOUR_SET_POINTS[previousHour];

  // Hour gauge pwm set point value for the new hour value in response to use pressing the set hour button
  int newHourSetPoint = HOUR_SET_POINTS[newHour];

  // Update the hour sample and set point so that when the clock is in running mode, it knows what hour it is and what set point for the hour to use
  lastHourSample = newHour;
  lastHourSetPoint = newHourSetPoint;

  // Update the real time clock, set seconds to zero by default
  RTC.h = newHour;
  RTC.s = 0;
  RTC.writeTime();

  // Debug
  Serial.print("Set Hour To:");
  Serial.println(RTC.h);

  // Smoothly move the needle from the old hour location to the new hour location
  smoothGauge(PIN_HOUR_GAUGE, previousHourSetPoint, newHourSetPoint);
}

void processButtonSetMinutes() {
  // Read current time from the RTC
  RTC.readTime();

  // Get the minute value from the RTC
  int previousMinute = RTC.m;

  // Increment the minute value in response to the user pressing the set minute button
  int newMinute = previousMinute + 1;

  // 60 seconds to a minute, if over 59, set the value to 0
  if (newMinute > 59) {
    newMinute = 0;
  }

  // Update he minute sample so it knows what the current minute is to later determine if the value changes
  lastMinuteSample = newMinute;

  // Set the RTC.  Set seconds to 0.
  RTC.m = newMinute;
  RTC.s = 0;
  RTC.writeTime();

  // Debug
  Serial.print("Set Minute To:");
  Serial.println(RTC.m);

  // Smoothly move the needle from the old minute location to the new minute location
  smoothGauge(PIN_MINUTE_GAUGE,
              map(previousMinute, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX),
              map(newMinute, 0, 59, GAUGE_MINUTE_MIN, GAUGE_MINUTE_MAX));
}

void processButtonSetColor() {
  // Increment the color index to the next one.
  unsigned int newRunColor = runColor + 1;

  // 1 based index in a zero based array hence the adjustment of -1.  If at the end of the color list, start at the beginning
  if (newRunColor > COLOR_COUNT - 1) {
    newRunColor = 1;
  }

  // Set the new color and update the global
  runColor = newRunColor;
  setRGBLEDs(COLORS[newRunColor]);

}
