#include "pin_mapping.h"
#include "buttons.h"
#include "leds.h"
#include "oled_display.h"

// disaster counter logic
unsigned int DAYS_COUNTER = 0;
void handle_button_press(const int& button_state, unsigned int& days_counter);

void setup() {
  buttons::setup_buttons();
  oled_display::setup_display();
  leds::setup_leds();
  
  while (leds::do_circle_animation())
  {
    oled_display::cycle_startup_oled_animation();
    delay(50);
  }

  oled_display::display_info(DAYS_COUNTER, leds::get_night_mode());

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
      oled_display::display_congrats();
      leds::do_mini_celebration();
      break;
    case 2:
      leds::toggle_night_mode();
      break;
    case 3:
      days_counter = 0;
      break;
    default:
      break;
  }
  oled_display::display_info(days_counter, leds::get_night_mode());
  leds::update_led_counter(days_counter);
}
