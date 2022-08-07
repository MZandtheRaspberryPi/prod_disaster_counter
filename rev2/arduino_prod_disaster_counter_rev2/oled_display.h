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

} // end namespace oled_display

#endif
