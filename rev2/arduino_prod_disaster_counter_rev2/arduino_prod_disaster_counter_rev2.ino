#include "pin_mapping.h"
#include "buttons.h"
#include "leds.h"
#include "oled_display.h"

// disaster counter logic
unsigned int DAYS_COUNTER = 9;
void handle_button_press(const int& button_state, unsigned int& days_counter);

void setup() {
  buttons::setup_buttons();
  //setup_display();
  oled_display::setup_display();
  leds::setup_leds();
  leds::do_startup_greeting();
  oled_display::display_info(DAYS_COUNTER);

}

void loop() {
  int button_state = buttons::is_button_pressed();
  handle_button_press(button_state, DAYS_COUNTER);
  delay(50);
}

void handle_button_press(const int& button_state, unsigned int& days_counter)
{
  switch (button_state)
  {
    case 1:
      days_counter++;
      leds::do_mini_celebration();
      oled_display::display_info(days_counter);
      leds::update_led_counter(days_counter);
      break;
    case 2:
      days_counter = 0;
      oled_display::display_info(days_counter);
      leds::update_led_counter(days_counter);
      break;
    default:
      break;
  }
}
