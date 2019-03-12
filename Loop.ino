void loop() {
  updateTimeGauges();

  while (!digitalRead(PIN_BUTTON_SET_HOURS) && !digitalRead(PIN_BUTTON_SET_MINUTES)) {
    parkGauges();
  }

  while (!digitalRead(PIN_BUTTON_SET_HOURS)) {
    processButtonSetHours();
    delay(300);
  }

  while (!digitalRead(PIN_BUTTON_SET_MINUTES)) {
    processButtonSetMinutes();
    delay(300);
  }

  while (!digitalRead(PIN_BUTTON_SET_COLOR)) {
    processButtonSetColor();
    delay(300);
  }

  delay(500);
}
