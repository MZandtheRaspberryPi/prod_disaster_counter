#include "disaster_logic.h"

namespace disaster_logic
{

  int days_without_incident = 0;
  int last_days_without_incident = 0;
  int first_day_check = 5;
  int second_day_check = 15;
  int third_day_check = 30;
  int fourth_day_check = 60;
  
  bool celebration_done = false;

void do_animation(LiquidCrystal& lcd, int red_led, int yellow_led, int green_led, int blue_led)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congrats!!!!");
  lcd.setCursor(0, 1);
  lcd.print(":)");

  int led_index = 0;
  unsigned long start_time = millis();
  int led_seq_time = 3000;
  while (millis() - start_time < led_seq_time)
  {
    switch (led_index)
    {
      case 0:
        digitalWrite(red_led, HIGH);
        digitalWrite(yellow_led, LOW);
        digitalWrite(green_led, LOW);
        digitalWrite(blue_led, LOW);
        break;
      case 1:
        digitalWrite(red_led, LOW);
        digitalWrite(yellow_led, HIGH);
        digitalWrite(green_led, LOW);
        digitalWrite(blue_led, LOW);
        break;
      case 2:
        digitalWrite(red_led, LOW);
        digitalWrite(yellow_led, LOW);
        digitalWrite(green_led, HIGH);
        digitalWrite(blue_led, LOW);
        break;
      case 3:
        digitalWrite(red_led, LOW);
        digitalWrite(yellow_led, LOW);
        digitalWrite(green_led, LOW);
        digitalWrite(blue_led, HIGH);
        break;
      default:
        break;
   }
   delay(50);
   if (led_index == 3)
   {
    led_index = 0;
   }
   else
   {
    led_index++;
   }
  }
}

void handle_button_press(unsigned long button_press_time)
{
  if (button_press_time != 0)
  {
      if (button_press_time > buttons::button_press_threshold)
      {
        days_without_incident = 0;
        last_days_without_incident = 0;
      }
      else
      {
        days_without_incident++;
      }
  }
}

void handle_count_logic(LiquidCrystal& lcd, int red_led, int yellow_led, int green_led, int blue_led)
{
  if (days_without_incident < first_day_check)
  {
    digitalWrite(red_led, LOW);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, LOW);
  }
  
  else if (days_without_incident < second_day_check)
  {
    if (days_without_incident - last_days_without_incident == first_day_check - 0 && days_without_incident == first_day_check)
    {
      last_days_without_incident = days_without_incident;
      do_animation(lcd, red_led, yellow_led, green_led, blue_led);
    }
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, LOW);
  }

  else if (days_without_incident < third_day_check)
  {
    if (days_without_incident - last_days_without_incident == second_day_check - first_day_check && days_without_incident == second_day_check)
    {
      last_days_without_incident = days_without_incident;
      do_animation(lcd, red_led, yellow_led, green_led, blue_led);
    }
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(blue_led, LOW);
  }


  else if (days_without_incident < fourth_day_check)
  {
    if (days_without_incident - last_days_without_incident == third_day_check - second_day_check && days_without_incident == third_day_check)
    {
      last_days_without_incident = days_without_incident;
      do_animation(lcd, red_led, yellow_led, green_led, blue_led);
    }
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, HIGH);
    digitalWrite(blue_led, LOW);
  }

  else
  {
    if (days_without_incident - last_days_without_incident == fourth_day_check - third_day_check && days_without_incident == fourth_day_check)
    {
      last_days_without_incident = days_without_incident;
      do_animation(lcd, red_led, yellow_led, green_led, blue_led);
    }
    digitalWrite(red_led, HIGH);
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, HIGH);
    digitalWrite(blue_led, HIGH);
  }
}

} // namespace disaster_logic
