#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>
#include <TinyI2CMaster.h>


namespace oled_display
{


void setup_display();
void display_header_row();
void display_counter_row(const int& days_without_incident);
void display_info(const unsigned int& days_without_incident, const bool& night_mode);
void display_congrats();
void cycle_startup_oled_animation();
void clear_display();
static byte x_position = 50;
static byte y_position = 0;
static byte bitmap_counter = 0;
static byte size_bitmap_x = 31;
static byte size_bitmap_y_num_pages = 4; // 32 pixels

// 'flower_0', 31x32px
const static unsigned char epd_bitmap_flower_0 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xe0, 0xf0, 0x78, 0x38, 
  0x38, 0x78, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0x7f, 0xf3, 0xe3, 0xc1, 0xc3, 0xc3, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x3c, 
  0x7c, 0xff, 0xff, 0xff, 0xc7, 0x83, 0x83, 0xc7, 0xff, 0xfe, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x70, 0xfc, 0xfe, 0xcf, 0x87, 0x83, 0x83, 0xc7, 0xff, 0xff, 0xfc, 0x7c, 0x78, 0x78, 0xfc, 
  0xff, 0xff, 0xff, 0x87, 0x87, 0x87, 0x8f, 0xff, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x0f, 0x3f, 0x3c, 0x70, 0x70, 0x78, 0x3c, 0x1f, 
  0x0f, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'flower_10', 31x32px
const static unsigned char epd_bitmap_flower_10 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 
  0x78, 0x38, 0x38, 0xf8, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x9f, 0xff, 0xfd, 0xf0, 0xe0, 0xe0, 0xf1, 0xff, 0xff, 0x7f, 0x3e, 0x3c, 
  0x78, 0xfc, 0xfc, 0xff, 0xff, 0x0e, 0x0e, 0x0e, 0x8e, 0xfc, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7e, 0xff, 0xe7, 0xe3, 0xc1, 0xc1, 0xe1, 0xff, 0xff, 0x7f, 0x7e, 0x78, 0x78, 0xf8, 0xf8, 
  0xff, 0xff, 0x1f, 0x0f, 0x0f, 0x1f, 0xff, 0xff, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x3f, 0x78, 0x70, 0x70, 0x38, 0x3f, 0x1f, 0x07, 
  0x07, 0x07, 0x0e, 0x0e, 0x0e, 0x07, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00
};
// 'flower_20', 31x32px
const static unsigned char epd_bitmap_flower_20 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x70, 0x70, 0x70, 0xe0, 0xe0, 0xc0, 0xc0, 
  0xe0, 0x70, 0x70, 0x30, 0x70, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0xc0, 0xc0, 0xef, 0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf8, 0xff, 0x7f, 0x3f, 0x3f, 
  0x7c, 0xf8, 0xf8, 0xf8, 0xff, 0x3f, 0x1f, 0x1c, 0x38, 0x38, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 
  0x1f, 0x3f, 0x3f, 0x71, 0x70, 0xf0, 0xf0, 0xfc, 0xff, 0x7f, 0x7f, 0x7e, 0xf8, 0xf8, 0xf8, 0xf8, 
  0xff, 0x3f, 0x1f, 0x1f, 0x3e, 0xfc, 0xfc, 0xce, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x3f, 0x38, 0x70, 0x70, 0x38, 0x3c, 0x1f, 0x0f, 0x07, 0x0f, 
  0x1e, 0x1c, 0x1c, 0x1c, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'flower_30', 31x32px
const static unsigned char epd_bitmap_flower_30 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf0, 0x38, 0x38, 0x38, 0x78, 0xf0, 0xe0, 
  0xc0, 0xc0, 0xe0, 0xe0, 0x70, 0x70, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0xe0, 0xf0, 0x70, 0x70, 0x3f, 0x3f, 0x7f, 0xf8, 0xf8, 0xf8, 0xf8, 0x7e, 0x3f, 0x3f, 
  0x7f, 0xfc, 0xf8, 0xf0, 0xf0, 0xfc, 0x7f, 0x7f, 0x70, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x03, 
  0x0f, 0x0f, 0x1e, 0x1c, 0xf8, 0xf8, 0xfc, 0x3e, 0x3f, 0x3f, 0x3f, 0xfe, 0xf8, 0xf8, 0xf8, 0xf8, 
  0x3e, 0x3f, 0x3f, 0x7f, 0xfc, 0xf8, 0xb8, 0x38, 0x3c, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0x1f, 0x1f, 0x38, 0x38, 0x38, 0x1c, 0x1e, 0x0f, 0x0f, 0x1f, 0x1e, 0x3c, 
  0x38, 0x38, 0x3c, 0x1f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'flower_40', 31x32px
const static unsigned char epd_bitmap_flower_40 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0x78, 0x3c, 0x1c, 0x38, 0x78, 
  0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xf0, 0xf8, 0xf8, 0x3c, 0x1c, 0x1c, 0x1c, 0x3f, 0xff, 0xfc, 0xf8, 0xf8, 0x7c, 0x3e, 0x3f, 
  0x7f, 0xff, 0xff, 0xf1, 0xe0, 0xe0, 0xf9, 0xff, 0xff, 0xc6, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x07, 0x0f, 0xee, 0xfe, 0xfc, 0x1e, 0x1f, 0x1f, 0x3f, 0xff, 0xfe, 0xf8, 0xf8, 0xf8, 0x78, 
  0x7f, 0x7f, 0xff, 0xff, 0xf1, 0xe0, 0xe0, 0x71, 0x71, 0x7f, 0x3f, 0x1e, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x0f, 0x1e, 0x1c, 0x1c, 0x1c, 0x0e, 0x0f, 0x07, 0x0f, 0x3f, 0x3c, 0x78, 0x70, 
  0x70, 0x7c, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'flower_50', 31x32px
const static unsigned char epd_bitmap_flower_50 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0x3c, 0x1c, 0x1c, 
  0x3c, 0xf8, 0xf0, 0xe0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xf8, 0xfc, 0xfe, 0x8e, 0x0e, 0x0e, 0x0e, 0x8e, 0xff, 0xff, 0xff, 0xfc, 0x78, 0x3c, 0x7c, 
  0x7f, 0xff, 0xff, 0xff, 0xe3, 0xc1, 0xc1, 0xe3, 0xff, 0x7f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xe1, 0xfb, 0xff, 0x3f, 0x0f, 0x0f, 0x0f, 0x1f, 0xff, 0xff, 0xfc, 0xf8, 0xf0, 0x78, 0x78, 
  0xff, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc7, 0xef, 0xff, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0x03, 0x07, 0x0f, 0x0e, 0x0e, 0x07, 0x07, 0x07, 0x0f, 0x3f, 0x7d, 0x70, 0x70, 0x70, 0x78, 
  0x7f, 0x3f, 0x0f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 864)
const static int epd_bitmap_allArray_LEN = 6;
const static unsigned char* epd_bitmap_allArray[6] = {
  epd_bitmap_flower_0,
  epd_bitmap_flower_10,
  epd_bitmap_flower_20,
  epd_bitmap_flower_30,
  epd_bitmap_flower_40,
  epd_bitmap_flower_50
};

// 'moon', 16x16px
const unsigned char epd_bitmap_moon [] PROGMEM = {
  0x00, 0x00, 0x00, 0xc0, 0x70, 0x18, 0x0c, 0x7c, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0x1e, 0x30, 0x20, 0x60, 0x41, 0x43, 0x66, 0x2c, 0x38, 0x18, 0x00, 0x00
};

} // end namespace oled_display

#endif
