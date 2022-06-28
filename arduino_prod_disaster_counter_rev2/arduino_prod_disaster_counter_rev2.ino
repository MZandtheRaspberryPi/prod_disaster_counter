#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include <FastLED.h>

// pin mapping
#define BUTTON_PIN 4
#define LED_PIN 1


// button logic
int BUTTON_STATE;             // the current reading from the input pin
const int BUTTON_PRESS_THRESHOLD = 1000; // milliseconds under which a button press will increment counter, over which, will clear counter
unsigned long START_BUTTON_PRESS = 0;

int is_button_pressed(const int& button_pin, const int& button_press_threshold, unsigned long& start_button_press);

// display logic
void setup_display();
void display_header_row();
void display_counter_row(const int& days_without_incident);
void display_info(const int& days_without_incident);
void display_congrats();

// disaster counter logic
int DAYS_COUNTER = 0;
void handle_button_press(const int& button_state, int& days_counter);


// led logic
#define NUM_LEDS 3
#define BRIGHTNESS  200
#define HUE_STEP 20
#define LED_CYCLE_DELAY  100
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
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
  //setup_display();
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  setup_display(DAYS_COUNTER);
}

void loop() {
  BUTTON_STATE = is_button_pressed(BUTTON_PIN, BUTTON_PRESS_THRESHOLD, START_BUTTON_PRESS);
  handle_button_press(BUTTON_STATE, DAYS_COUNTER);
  delay(50);
}

void setup_display(const int& days_counter)
{
  // Send the initialization sequence to the oled. This leaves the display turned off
  oled.begin(0, 0);
  // The default state of the SSD1306 does not turn on the internal charge pump
  oled.enableChargePump();
  oled.setFont(FONT6X8);
  oled.setRotation(1);
  // In order to use double buffering on the 128x64 screen,
  // the zoom feature needs to be used, which doubles the height
  // of all pixels.
  oled.enableZoomIn();
  // Clear the memory before turning on the display
  oled.clear();
  // Turn on the display
  oled.on();
  display_info(days_counter);
}

void display_header_row()
{
  // Position the text cursor
  // In order to keep the library size small, text can only be positioned
  // with the top of the font aligned with one of the four 8 bit high RAM pages.
  // The Y value therefore can only have the value 0, 1, 2, or 3.
  // usage: oled.setCursor(X IN PIXELS, Y IN ROWS OF 8 PIXELS STARTING WITH 0);
  oled.setCursor(0, 0);
  // Write text to oled RAM (which is not currently being displayed).
  oled.print(F("One Day-One Step"));


}
void display_counter_row(const int& days_without_incident)
{  
  oled.setCursor(0, 3);
  oled.print(F("You're at: "));
  oled.print(days_without_incident);
}
void display_info(const int& days_without_incident)
{
  // Clear the half of memory not currently being displayed.
  oled.clear();
  display_header_row();
  display_counter_row(DAYS_COUNTER);
}

void display_congrats()
{
  // Clear the half of memory not currently being displayed.
  oled.clear();
  oled.setCursor(0, 0);
  // Write text to oled RAM (which is not currently being displayed).
  oled.print(F("Congrats!!!"));
}


int is_button_pressed(const int& button_pin, const int& button_press_threshold, unsigned long& start_button_press)
{
  if (digitalRead(button_pin) == HIGH)
  {
    start_button_press = millis();
    // wait till button is let go
    while (digitalRead(button_pin) == HIGH)
    {
      delay(10);
    }

    if (millis() - start_button_press > button_press_threshold)
    {
      return 2;
    }
    else
    {
      return 1;
    }

  }
  else
  {
    return 0;
  }
}


void handle_button_press(const int& button_state, int& days_counter)
{
  switch (button_state)
  {
    case 1:
      days_counter++;
      do_mini_celebration(leds, HSV_HUE, HSV_SATURATION, LED_ITERATOR, NUM_LEDS, HUE_STEP, ENDING_HSV_HUE, LED_CYCLE_DELAY, MIN_SATURATION, MAX_SATURATION);
      display_info(days_counter);
      break;
    case 2:
      days_counter = 0;
      display_info(days_counter);
      break;
    default:
      break;
  }
}

void do_mini_celebration(CRGB* leds, byte& hsv_hue, byte& hsv_saturation, byte& led_iterator,
                         const int & num_leds, const int & hue_step, byte & ending_hsv_hue,
                         const int & led_cycle_delay, const int & min_saturation, const int & max_saturation)
{
  display_congrats();
  // pick a starting point for the rainbow
  hsv_hue = random(0, 256);
  hsv_saturation = random(min_saturation, max_saturation);
  ending_hsv_hue = hsv_hue - hue_step - 1;
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
