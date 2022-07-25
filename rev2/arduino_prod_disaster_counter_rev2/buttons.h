#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

#include "pin_mapping.h"

namespace buttons
{

  struct button_working_mem_t
  {
    int button_state;
    unsigned long start_button_press;
    unsigned long button_press_length;
  };

  struct button_settings_t
  {
    int button_press_threshold_1 = 1000; // under this threshold, we will increment day counter
    int button_press_threshold_2 = 5000; // between threshold 1 and this, we will turn on night mode for leds. over this, we will clear counter.
  };

  static button_working_mem_t button_working_mem{};
  static button_settings_t button_settings{};

  void setup_buttons();
  
  int is_button_pressed();
    
} // end namespace buttons

#endif
