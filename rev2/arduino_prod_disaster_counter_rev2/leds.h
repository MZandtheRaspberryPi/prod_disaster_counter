#ifndef LEDS_H
#define LEDS_H
#include <Arduino.h>
#include <FastLED.h>

#include "pin_mapping.h"

namespace leds
{

  struct led_settings_t
  {
    const byte hue_step = 20;
    const byte led_celebration_cycle_delay = 20;
    const byte led_circle_cycle_delay = 100;
    const int min_saturation = 150;
    const int max_saturation = 256;
    const byte night_mode_brightness = 20;
    const byte day_mode_brightness = 200;
    byte startup_hue_iteration_move = 4;
  };

  struct led_working_mem_t
  {
    CHSV hsv_color;
    byte ending_hsv_hue;
    byte led_iterator;
    bool night_mode;
    // used for startup circle animation
    unsigned long start_time;
    unsigned long last_led_flip_time;
    byte startup_ending_led;
    bool exit_flag;
    byte ending_led;
  };

  void setup_leds();
  bool get_night_mode();

  void do_mini_celebration();
  bool do_circle_animation();

  void toggle_night_mode();
  
  void update_led_counter(const unsigned int & days_counter);
    
} // end namespace leds

#endif
