/* Library Includes */
#include <Wire.h>
#include <MD_DS3231.h>

/* Associated with buttons */
#define BUTTON_NOT_PRESSED      HIGH
#define BUTTON_PRESSED          LOW

/* Arduino Nano Pin Assignments */
#define PIN_BUTTON_SET_HOURS    2         // Button to select the editing mode. (Hour, Minute, Second, Light Color)
#define PIN_BUTTON_SET_MINUTES  4         // Button increments the value you are editing in the selected editing mode.
#define PIN_BUTTON_SET_COLOR    7         // Button decrements the value you are editing in the selected editing mode.
#define PIN_LED_RED             3         // Red channel for RGB leds.
#define PIN_LED_GREEN           5         // Green channel for RGB leds.
#define PIN_LED_BLUE            6         // Blue channel for RGB leds.
#define PIN_HOUR_GAUGE          9         // Volt meter gauge that represents the hours.
#define PIN_MINUTE_GAUGE        10        // Volt meter gauge that represents the minutes.
#define PIN_SECOND_GAUGE        11        // Volt meter gauge that represents the seconds.

/* Available colors for the gauges while running */
#define COLOR_RED               0
#define COLOR_GREEN             1
#define COLOR_BLUE              2
#define COLOR_PURPLE            3
#define COLOR_CYAN              4
#define COLOR_ORANGE            5
#define COLOR_YELLOW            6
#define COLOR_WHITE             7
#define COLOR_INDIGO            8
#define COLOR_BLACK             9
#define COLOR_COUNT             10        // How many colors are available, used for cycling through the colors when changing the run color.

/* Set the direction to have the time gauges move. */
#define SMOOTH_GAUGE_DOWN       0
#define SMOOTH_GAUGE_UP         1
#define SMOOTH_GAUGE_SPEED      3         // In milliseconds, the delay between each needle update.

/* Define the type of LED animation to use in LedAnimation method. */
#define LED_ANIMATION_BLINK     0
#define LED_ANIMATION_RANDOM    1
/* Used to access the index of each color value in a COLORS array to set the proper color in the RGB LED. */
#define LED_RED                 0
#define LED_GREEN               1
#define LED_BLUE                2

/* Fine tune the maximum PWM value for the gauges */
#define GAUGE_HOUR_MAX          255
#define GAUGE_MINUTE_MAX        238
#define GAUGE_SECOND_MAX        255

/* Fine tune the minimum PWM value for the gauges */
#define GAUGE_HOUR_MIN          0
#define GAUGE_MINUTE_MIN        0
#define GAUGE_SECOND_MIN        0

#define GAUGE_PARK_TIME         30000     // In milliseconds.

/* RGB definitions for the available colors to set the LEDs. */
const int COLORS[COLOR_COUNT][3] = {
  {255, 0, 0},          // Red
  {0, 255, 0},          // Green
  {0, 0, 255},          // Blue
  {100, 0, 50},         // Purple
  {0, 200, 255},        // Cyan
  {255, 20, 0},         // Orange
  {255, 100, 0},        // Yellow
  {255, 255, 255},      // Kinda White
  {75, 0, 130},         // Indigo
  {0, 0, 0}             // Black (Off)
};

const int HOUR_SET_POINTS[13] = {0, 16, 38, 60, 81, 103, 123, 146, 167, 187, 208, 230, 252}; // 1 based index.

  /* The color used for the LEDs while the clock is running */
  unsigned int runColor = COLOR_WHITE;

  unsigned int lastHourSample = 0;
  unsigned int lastMinuteSample = 0;
  unsigned int lastSecondSample = 0;

  unsigned int lastHourSetPoint = 0;
