#include "buttons.h"

namespace buttons
{

  int BUTTON_STATE;             // the current reading from the input pin
  int button_press_threshold = 1000; // milliseconds under which a button press will increment counter, over which, will clear counter

  unsigned long is_button_pressed(const int& button_pin)
  {
    int reading = digitalRead(button_pin);
    if (reading == HIGH)
    {
      unsigned long start_button_press = millis();
      // wait till button is let go
      while (digitalRead(button_pin))
      {
        delay(10);
      }
      return millis() - start_button_press;
    }
    else
    {
      return 0;
    }
  }
    

} // end namespace buttons
