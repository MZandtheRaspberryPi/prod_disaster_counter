#include "buttons.h"

namespace buttons
{
  
  void setup_buttons()
  {
    // initialize the pushbutton pin as an input:
    pinMode(pin_mapping::BUTTON_PIN, INPUT);
    button_working_mem.button_state = 0;
    button_working_mem.start_button_press = 0;
  }
  
  
  int is_button_pressed()
  {
    if (digitalRead(pin_mapping::BUTTON_PIN) == HIGH)
    {
      button_working_mem.start_button_press = millis();
      // wait till button is let go
      while (digitalRead(pin_mapping::BUTTON_PIN) == HIGH)
      {
        delay(10);
      }
      button_working_mem.button_press_length = millis() - button_working_mem.start_button_press;
      if (button_working_mem.button_press_length < button_settings.button_press_threshold_1)
      {
        return 1;
      }
      else if (button_working_mem.button_press_length >= button_settings.button_press_threshold_1
      && button_working_mem.button_press_length < button_settings.button_press_threshold_2)
      {
        return 2;
      }
      else if (button_working_mem.button_press_length >= button_settings.button_press_threshold_2)
      {
        return 3;
      }
      else
      {
        return 0;  
      }
    }
    else
    {
      return 0;
    }
  }
    
} // end namespace buttons
