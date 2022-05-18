#include <LiquidCrystal.h>

#include "buttons.h"
#include "disaster_logic.h"
#include "display.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 4, d4 = 5, d5 = 11, d6 = 12, d7 = 13, v0 = 2;

const int red_led = 7, yellow_led = 8, green_led = 9, blue_led = 10;
const int button_pin = 6;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //Declaring LED pin as output
  pinMode(red_led, OUTPUT);
   //Declaring LED pin as output
  pinMode(yellow_led, OUTPUT);
   //Declaring LED pin as output
  pinMode(green_led, OUTPUT);
   //Declaring LED pin as output
  pinMode(blue_led, OUTPUT);

  // initialize the pushbutton1 pin as an input:
  pinMode(button_pin, INPUT);

  //Declaring LED pin as output
  pinMode(blue_led, OUTPUT);

  analogWrite(v0, display::CONTRAST);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

}

void loop() {
  unsigned long button_press_time = buttons::is_button_pressed(button_pin);
  disaster_logic::handle_button_press(button_press_time);
  display::display_info(lcd, disaster_logic::days_without_incident);
  disaster_logic::handle_count_logic(lcd, red_led, yellow_led, green_led, blue_led);
}
