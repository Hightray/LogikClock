void setup() {
  Serial.begin(115200);

  /* Wait until the Serial device is available before proceeding. */
  while (!Serial) {
    ;
  }

  /* Enable pullup resistor on the button pins. */
  pinMode(PIN_BUTTON_SET_HOURS, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SET_MINUTES, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SET_COLOR, INPUT_PULLUP);

  /* Set the RTC clock to run in 12 hour mode. */
  RTC.control(DS3231_12H, DS3231_ON);

  initializeLEDs();
  initializeGauges();
  
  Serial.println("Ready.");
}
