#include "leds.h"

namespace leds
{

  const static int hue_increment_value = 20;
  const static CHSV startup_color_yellow( 39, 209, 255);

  static const int NUM_LEDS = 10;

  static led_working_mem_t led_working_mem{};
  static const led_settings_t led_settings{};
  static CRGB leds[NUM_LEDS];


  void setup_leds()
  {
    FastLED.addLeds<WS2812B, pin_mapping::LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(led_settings.day_mode_brightness);
    FastLED.clear();
    FastLED.show();
    led_working_mem.hsv_color = startup_color_yellow;
    led_working_mem.night_mode = false;

    // this is for the startup led animation
    led_working_mem.startup_ending_led = 9;
    led_working_mem.exit_flag = false;
    led_working_mem.start_time = millis();
    led_working_mem.last_led_flip_time = millis();
    led_working_mem.hsv_color = startup_color_yellow;
    led_working_mem.led_iterator = 0;
    led_working_mem.ending_led = 9;
  }

  void toggle_night_mode()
  {
    led_working_mem.night_mode = !led_working_mem.night_mode;
    if (led_working_mem.night_mode)
    {
      FastLED.setBrightness(led_settings.night_mode_brightness);
    }
    else
    {
      FastLED.setBrightness(led_settings.day_mode_brightness);
    }
  }

  bool get_night_mode()
  {
    return led_working_mem.night_mode;
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
    led_working_mem.hsv_color = startup_color_yellow;
    FastLED.clear();
    if (ones_digit > 0)
    {
      leds[ones_digit - 1] = led_working_mem.hsv_color;
    }
    led_working_mem.hsv_color.hue -= hue_increment_value;
    if (tens_digit > 0)
    {
      leds[tens_digit - 1] = led_working_mem.hsv_color;
    }
    led_working_mem.hsv_color.hue -= hue_increment_value;    
    if (hundreds_digit > 0)
    {
      leds[hundreds_digit - 1] = led_working_mem.hsv_color;
    }
    led_working_mem.hsv_color.hue -= hue_increment_value;
    if (thousands_digit > 0)
    {
      leds[thousands_digit - 1] = led_working_mem.hsv_color;
    }
    led_working_mem.hsv_color.hue -= hue_increment_value;
    if (ten_thousdands_digit > 10)
    {
      ten_thousdands_digit = 10;
    }
    if (ten_thousdands_digit > 0)
    {
      leds[ten_thousdands_digit - 1] = led_working_mem.hsv_color;
    }
    FastLED.show();
  }

  // must call setup_leds before this
  bool do_circle_animation()
  {
    
    if (millis() - led_working_mem.last_led_flip_time > led_settings.led_circle_cycle_delay)
    {
      // turn off prior led
      if (led_working_mem.led_iterator > 0)
      {
        leds[led_working_mem.led_iterator - 1] = CRGB::Black;
      }
      leds[led_working_mem.led_iterator] = led_working_mem.hsv_color;
      
      FastLED.show();
      if (led_working_mem.led_iterator == led_working_mem.ending_led)
      {
        led_working_mem.led_iterator = 0;
        led_working_mem.ending_led--;
        led_working_mem.hsv_color.hue -= led_settings.startup_hue_iteration_move;
      }
      else
      {
        led_working_mem.led_iterator++;
      }
      led_working_mem.last_led_flip_time = millis();
    }

      
    if (led_working_mem.ending_led == 255)
    {
      led_working_mem.exit_flag = true;
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 50; j++)
        {
          FastLED.setBrightness(led_settings.day_mode_brightness - j * 2);
          FastLED.show();
          delay(led_settings.led_celebration_cycle_delay);
        }

        for (int j = 50; j >= 0; j--)
        {
          FastLED.setBrightness(led_settings.day_mode_brightness - j * 2);
          FastLED.show();
          delay(led_settings.led_celebration_cycle_delay);
        }
      }
      FastLED.clear();
      FastLED.show();
    }
    return !led_working_mem.exit_flag;
  }
  
  
  void do_mini_celebration()
  {
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
        delay(led_settings.led_celebration_cycle_delay);
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
