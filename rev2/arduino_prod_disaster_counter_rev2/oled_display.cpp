#include "oled_display.h"
// The blue OLED screen requires a long initialization on power on.
// The code to wait for it to be ready uses 20 bytes of program storage space
// If you are using a white OLED, this can be reclaimed by uncommenting
// the following line (before including Tiny4kOLED.h):
#define TINY4KOLED_QUICK_BEGIN
#include <Tiny4kOLED.h>
namespace oled_display
{


  void display_header_row()
  {
    // Position the text cursor
    // In order to keep the library size small, text can only be positioned
    // with the top of the font aligned with one of the four 8 bit high RAM pages.
    // The Y value therefore can only have the value 0, 1, 2, or 3.
    // usage: oled.setCursor(X IN PIXELS, Y IN ROWS OF 8 PIXELS STARTING WITH 0);
    oled.setCursor(0, 0);
    // Write text to oled RAM (which is not currently being displayed).
    oled.print(F("Daily Counter"));
  
  
  }
  void display_counter_row(const unsigned int& days_without_incident)
  {  
    oled.setCursor(0, 2);
    oled.print(F("You're at: "));
    oled.print(days_without_incident);
  }
  void display_info(const unsigned int& days_without_incident, const bool& night_mode)
  {
    // Clear the half of memory not currently being displayed.
    oled.clear();
    display_header_row();
    display_counter_row(days_without_incident);
    if (night_mode)
    {
      oled.bitmap(111, 2, 127, 4, epd_bitmap_moon);
    }
    oled.switchFrame();
  }
  
  void display_congrats()
  {
    // Clear the half of memory not currently being displayed.
    oled.clear();
    oled.setCursor(0, 0);
    // Write text to oled RAM (which is not currently being displayed).
    oled.print(F("Congrats!!!"));
    oled.switchFrame();
  }
  
  void clear_display()
  {
    oled.clear();
    oled.switchFrame();
  }
  
  void cycle_startup_oled_animation()
  {
      oled.bitmap(x_position, y_position, x_position + size_bitmap_x, size_bitmap_y_num_pages, epd_bitmap_allArray[bitmap_counter]);
      // Switch back to being ready to render on the first frame while displaying the second frame.
      oled.switchFrame();
      oled.clear();
      bitmap_counter += 1;
      if (bitmap_counter == epd_bitmap_allArray_LEN)
      {
        bitmap_counter = 0;
      }
  }

  void setup_display()
  {
    // Send the initialization sequence to the oled. This leaves the display turned off
    oled.begin(0, 0);
    // The default state of the SSD1306 does not turn on the internal charge pump
    oled.enableChargePump();
    oled.setRotation(1);
    // In order to use double buffering on the 128x64 screen,
    // the zoom feature needs to be used, which doubles the height
    // of all pixels.
    oled.enableZoomIn();
    oled.setFont(FONT6X8);
    // Clear the memory before turning on the display
    oled.clear();
    // Switch the half of RAM that we are writing to, to be the half that is non currently displayed
    oled.switchRenderFrame();
    oled.clear();
    oled.bitmap(x_position, y_position, x_position + size_bitmap_x, size_bitmap_y_num_pages, epd_bitmap_allArray[bitmap_counter]);
    // Switch back to being ready to render on the first frame while displaying the second frame.
    oled.switchFrame();
    // Turn on the display
    oled.on();
  }
} // end namespace oled_display
