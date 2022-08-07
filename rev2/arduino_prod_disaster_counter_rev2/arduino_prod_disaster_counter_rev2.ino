#include <EEPROM.h>

#include "buttons.h"
#include "leds.h"
#include "oled_display.h"

// disaster counter logic
unsigned int DAYS_COUNTER = 0;
int address = 0;
void handle_button_press(const int& button_state, unsigned int& days_counter);
void set_days_counter_eeprom(const int& days_counter, const int& address);
void get_days_counter_eeprom(int& days_counter, const int& address);

void setup() {
  // check if we have already saved DAYS_COUNTER to EEPROM

  if (EEPROM.read(address) == 255 && EEPROM.read(address + 1) == 255)
  {
    set_days_counter_eeprom(DAYS_COUNTER, address);
  }
  else
  {
    get_days_counter_eeprom(DAYS_COUNTER, address);
  }
  
  
  buttons::setup_buttons();
  oled_display::setup_display();
  leds::setup_leds();

  
  while (leds::do_circle_animation())
  {
    oled_display::cycle_startup_oled_animation();
    delay(20);
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
      set_days_counter_eeprom(days_counter, address);
      oled_display::display_congrats();
      leds::do_mini_celebration();
      break;
    case 2:
      leds::toggle_night_mode();
      break;
    case 3:
      days_counter = 0;
      set_days_counter_eeprom(days_counter, address);
      break;
    default:
      break;
  }
  oled_display::display_info(days_counter, leds::get_night_mode());
  leds::update_led_counter(days_counter);
}

void set_days_counter_eeprom(const unsigned int& days_counter, const int& address)
{
    //byte byte1 = days_counter >> 8;
    //byte byte2 = days_counter & 0xFF;
    //EEPROM.write(address, byte1);
    //EEPROM.write(address + 1, byte2);
    EEPROM.put(address, days_counter);
}

void get_days_counter_eeprom(unsigned int& days_counter, const int& address)
{
    //byte byte1 = EEPROM.read(address);
   // byte byte2 = EEPROM.read(address + 1);
    //days_counter =  (byte1 << 8) + byte2;
    EEPROM.get(address, days_counter);
}
