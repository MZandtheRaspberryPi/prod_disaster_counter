#include "leds.h"

namespace leds
{

  void setup_leds()
  {
    FastLED.addLeds<WS2812B, pin_mapping::LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(led_settings.brightness);
    FastLED.clear();
    FastLED.show();
    led_working_mem.hsv_color = startup_color_yellow;
  }


  void update_led_counter(const unsigned int & days_counter)
  {
    // update the 1s digit to be the current led lit up
    // if the 10s digit will be a permanent led
    // if we get to 100s digit, will be a diff color, moving a fair bit in hsv space
    byte ones_digit = days_counter % 10;
    byte tens_digit = floor(days_counter/10);
    byte hundreds_digit = floor(days_counter/100);
    byte thousands_digit = floor(days_counter / 1000);
    // if we count 10,000 9 times, that is 90,000 count.
    // if we assume one count per day, that is 246 years.
    // we will stop at counting 10,0000 digits
    byte ten_thousdands_digit = floor(days_counter / 10000);
    // do tens first, ten thousands last. so that ten thousands overwrites the tens for example.
    FastLED.clear();
    if (ones_digit > 0)
    {
      leds[ones_digit - 1] = startup_color_yellow;
    }
    if (tens_digit > 0)
    {
      leds[tens_digit - 1] = tens_color;
    }
    if (hundreds_digit > 0)
    {
      leds[hundreds_digit - 1] = hundreds_color;
    }
    if (thousands_digit > 0)
    {
      leds[thousands_digit - 1] = thousands_color;
    }
    if (ten_thousdands_digit > 10)
    {
      ten_thousdands_digit = 10;
    }
    if (ten_thousdands_digit > 0)
    {
      leds[ten_thousdands_digit - 1] = ten_thousands_color;
    }
    FastLED.show();
  }


  
  void do_startup_greeting()
  {
  
    // create a new RGB color
    
    unsigned long start_time = millis();
    unsigned long last_led_flip_time = millis();
    byte hue_iteration_move = 4;
    byte ending_led = 9;
    bool exit_flag = false;
    led_working_mem.hsv_color = startup_color_yellow;
    while (!exit_flag)
    {
      if (millis() - last_led_flip_time > led_settings.led_cycle_delay)
      {
        // turn off prior led
        if (led_working_mem.led_iterator > 0)
        {
          leds[led_working_mem.led_iterator - 1] = CRGB::Black;
        }
        leds[led_working_mem.led_iterator] = led_working_mem.hsv_color;
        
        FastLED.show();
        if (led_working_mem.led_iterator == ending_led)
        {
          led_working_mem.led_iterator = 0;
          ending_led--;
          led_working_mem.hsv_color.hue -= hue_iteration_move;
        }
        else
        {
          led_working_mem.led_iterator++;
        }
        last_led_flip_time = millis();
      }
      
      oled_display::cycle_startup_oled_animation();
      
      delay(50);
      if (ending_led == 255)
      {
        exit_flag = true;
      }
    }
  
  
    led_working_mem.hsv_color.hue = led_working_mem.hsv_color.hue + (hue_iteration_move * NUM_LEDS);
    oled_display::clear_display();
    oled_display::switch_frame();
  
    for (int i = 0; i < 3; i++)
    {
      int fade_counter = 0;
      while (fade_counter < 50)
      {
        for (int j = NUM_LEDS - 1; j >= 0; j --)
        {
          leds[j].setHSV(led_working_mem.hsv_color.hue - (hue_iteration_move * ((NUM_LEDS - 1) - j)), led_working_mem.hsv_color.saturation, led_working_mem.hsv_color.value - fade_counter * 2);
        }
        FastLED.show();
        delay(20);
        fade_counter++;
      }
  
      while (fade_counter >= 0)
      {
        for (int j = NUM_LEDS - 1; j >= 0; j --)
        {
          leds[j].setHSV(led_working_mem.hsv_color.hue - (hue_iteration_move * ((NUM_LEDS - 1) - j)), led_working_mem.hsv_color.saturation, led_working_mem.hsv_color.value - fade_counter * 2);
        }
        FastLED.show();
        delay(20);
        fade_counter--;
      }
  
    }
  
    FastLED.clear();
    FastLED.show();
    oled_display::clear_display();
    oled_display::switch_frame();
  }
  
  
  void do_mini_celebration()
  {
    oled_display::display_congrats();
    // pick a starting point for the rainbow
    led_working_mem.hsv_color.hue = random(0, 256);
    led_working_mem.hsv_color.saturation = random(led_settings.min_saturation, led_settings.max_saturation);
    led_working_mem.ending_hsv_hue = led_working_mem.hsv_color.hue - led_settings.hue_step - 1;
    while (abs(led_working_mem.hsv_color.hue - led_working_mem.ending_hsv_hue) > led_settings.hue_step )
    {
      for (led_working_mem.led_iterator = 0; led_working_mem.led_iterator < NUM_LEDS; led_working_mem.led_iterator++)
      {
        FastLED.clear();
        leds[led_working_mem.led_iterator].setHSV(led_working_mem.hsv_color.hue, led_working_mem.hsv_color.saturation, led_working_mem.hsv_color.value);
        FastLED.show();
        delay(led_settings.led_cycle_delay);
      }
      led_working_mem.hsv_color.hue += led_settings.hue_step;
    }
    FastLED.clear();
    FastLED.show();
    // rainbow left a couple times
    // rainbow right a couple times
    // blink them all in synchony a couple times
    // blink them all crazily a couple times
  }

  
} //end namespace leds
