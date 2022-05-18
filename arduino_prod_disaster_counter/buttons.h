#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

namespace buttons
{

  extern int BUTTON_STATE;             // the current reading from the input pin
  extern int button_press_threshold; // milliseconds under which a button press will increment counter, over which, will clear counter

  unsigned long is_button_pressed(const int& button_pin);
    
} // end namespace buttons

#endif
