#include "display.h"

namespace display
{

  int CONTRAST = 5;
  unsigned long last_text_scroll_time = 0;
  const int scroll_delay = 1000;
  int current_scroll_index = 0;
  // 'B', 'L', 'K', ' ', 
  char top_line[] = {'P', 'R', 'O', 'D', ' ', 'D', 'I', 'S', 'A', 'S', 'T', 'E', 'R', ' ', 'C', 'T', 'R'};
  const int text_len = sizeof(top_line)/sizeof(top_line[0]);

  void display_header_row(LiquidCrystal& lcd)
  {
    if (millis() - last_text_scroll_time > scroll_delay)
    {
      // put your main code here, to run repeatedly:
      lcd.clear();
      lcd.setCursor(0, 0);
      for (int i = current_scroll_index; i < text_len; i++)
      {
        lcd.print(top_line[i]);
      }
      if (current_scroll_index == text_len)
      {
        current_scroll_index = 0;
      }
      else
      {
        current_scroll_index++;
      }
      last_text_scroll_time = millis();
    }
  }

  void display_counter_row(LiquidCrystal& lcd, int days_without_incident)
  {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    lcd.print("Days w/o: ");
    // print the number of seconds since reset:
    lcd.setCursor(10, 1);
    lcd.print(days_without_incident);
  }

  void display_info(LiquidCrystal& lcd, int days_without_incident)
  {
    display_header_row(lcd);
    display_counter_row(lcd, days_without_incident);
  }
  

} // end namespace display
