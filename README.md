# LogikClock
Arduino clock software for voltmeter clock build.

This code is for driving an Arduino board, in my particular case a Arduino Nano.  The hardware associated with this code for
my use is:

  * Genuine Arduino Nano
  * DS3231 Real time clock
  * Three push buttons (connected to pins 2, 4, 7 on the Arduino Nano)
  * Three 0-300V AC current gauges (capacitor, resistor, diode removed -- direct connection to pin 9, 10, 11 on Arduino Nano)
  * Three RGB LEDs (connected to pins 3, 5, 6 on the Ardiuno Nano)

Workings:

  Button (Pin 7) is used for changing the colors of the LEDs (predefined colors)
  Button (Pin 2) is used for setting the hours component of the clock.  Results are shown on the hours gauge in real time.
  Button (Pin 4) is used for setting the minutes component of the clock.  Results are shown on the minutes gauge in real time.
  Pressing buttons (Pin 2 and Pin 4) at the same time will put the needles on the gauges in a parked position for unpluggin
  the device.  Although not required, I did not like the fact that when the power is removed, the needles on the gauges would
  slam down.  This gently places the needles in the off position for 30 seconds.  If the power is not removed from the device
  by then, normal clock functioning will resume.
  
Libraries:
  MD_DS3231 by majicDesigns - https://github.com/MagicDesigns/MD_DS3231
  
Feel free to use this code for your own projects, just please make a citation of where your work was derived from.

No warranties in any form are provided or implied for the functionailty or fitness of this code.
