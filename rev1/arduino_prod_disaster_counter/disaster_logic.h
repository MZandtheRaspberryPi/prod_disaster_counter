#ifndef DISASTER_LOGIC_H
#define DISASTER_LOGIC_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "buttons.h"

namespace disaster_logic
{

  extern int days_without_incident;
  extern int last_days_without_incident;
  extern int first_day_check;
  extern int second_day_check;
  extern int third_day_check;
  extern int fourth_day_check;
  
  extern bool celebration_done;

  void do_animation(LiquidCrystal& lcd, int red_led, int yellow_led, int green_led, int blue_led);

  void handle_button_press(unsigned long button_press_time);
  void handle_count_logic(LiquidCrystal& lcd, int red_led, int yellow_led, int green_led, int blue_led);
 
  
} // namespace disaster_logic

#endif
