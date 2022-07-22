#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

namespace display
{
  extern int CONTRAST;
  extern unsigned long last_text_scroll_time;
  extern const int scroll_delay;
  extern int current_scroll_index;
  extern char top_line[];
  extern const int text_len;

  
  void display_header_row(LiquidCrystal& lcd);
  void display_counter_row(LiquidCrystal& lcd, int days_without_incident);
  void display_info(LiquidCrystal& lcd, int days_without_incident);
  
} // end namespace lcd

#endif
