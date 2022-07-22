#ifndef LEDS_H
#define LEDS_H
#include <Arduino.h>
#include <FastLED.h>

#include "pin_mapping.h"
#include "oled_display.h"

namespace leds
{

  struct led_settings_t
  {
    const byte brightness = 200;
    const byte hue_step = 20;
    const byte led_cycle_delay = 50;
    const int min_saturation = 150;
    const int max_saturation = 256;
  };

  struct led_working_mem_t
  {
    CHSV hsv_color;
    byte ending_hsv_hue;
    byte led_iterator;
  };

  const static int hue_increment_value = 20;
  const static CHSV startup_color_yellow( 39, 209, 255);
  const static CHSV tens_color( startup_color_yellow.hue + hue_increment_value, startup_color_yellow.saturation, startup_color_yellow.value);
  const static CHSV hundreds_color( tens_color.hue + hue_increment_value, tens_color.saturation, tens_color.value);
  const static CHSV thousands_color( hundreds_color.hue + hue_increment_value, hundreds_color.saturation, hundreds_color.value);
  const static CHSV ten_thousands_color( thousands_color.hue + hue_increment_value, thousands_color.saturation, thousands_color.value);

  static const int NUM_LEDS = 10;

  static led_working_mem_t led_working_mem{};
  static const led_settings_t led_settings{};
  static CRGB leds[NUM_LEDS];

  void setup_leds();

  void do_mini_celebration();
  void do_startup_greeting();

  
  void update_led_counter(const unsigned int & days_counter);
    
} // end namespace leds

#endif
