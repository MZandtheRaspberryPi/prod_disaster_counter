#include <FastLED.h>

#define NUM_LEDS 1
#define BRIGHTNESS  200
#define HUE_STEP 20
#define LED_CYCLE_DELAY  100
#define LED_PIN 1
#define MIN_SATURATION 150
#define MAX_SATURATION 256
byte HSV_HUE;
byte HSV_SATURATION;
byte ENDING_HSV_HUE;
byte LED_ITERATOR = 0;
CRGB leds[NUM_LEDS];
void do_mini_celebration(CRGB* leds, byte& hsv_hue, byte& hsv_saturation, byte& led_iterator,
                         const int & num_leds, const int & hue_step, byte & starting_hsv_hue,
                         const int & led_cycle_delay);

void setup() {
  // put your setup code here, to run once:

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  do_mini_celebration(leds, HSV_HUE, HSV_SATURATION, LED_ITERATOR, NUM_LEDS, HUE_STEP, ENDING_HSV_HUE, LED_CYCLE_DELAY, MIN_SATURATION, MAX_SATURATION);
}



void do_mini_celebration(CRGB* leds, byte& hsv_hue, byte& hsv_saturation, byte& led_iterator,
                         const int & num_leds, const int & hue_step, byte & ending_hsv_hue,
                         const int & led_cycle_delay, const int & min_saturation, const int & max_saturation)
{
  // pick a starting point for the rainbow
  hsv_hue = random(0, 256);
  hsv_saturation = random(min_saturation, max_saturation);
  ending_hsv_hue = hsv_hue - hue_step;

  FastLED.show();
  while (abs(hsv_hue - ending_hsv_hue) > hue_step )
  {
    for (led_iterator = 0; led_iterator < num_leds; led_iterator++)
    {
      FastLED.clear();
      leds[led_iterator].setHSV(hsv_hue, hsv_saturation, 255);
      FastLED.show();
      delay(led_cycle_delay);
    }
    hsv_hue += hue_step;
  }
  // rainbow left a couple times
  // rainbow right a couple times
  // blink them all in synchony a couple times
  // blink them all crazily a couple times
}
