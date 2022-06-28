// pin mapping
#define BUTTON_PIN 8

// button logic
int BUTTON_STATE;             // the current reading from the input pin
const int BUTTON_PRESS_THRESHOLD = 1000; // milliseconds under which a button press will increment counter, over which, will clear counter
unsigned long START_BUTTON_PRESS = 0;

int is_button_pressed(const int& button_pin, const int& button_press_threshold, unsigned long& start_button_press)
{
  if (digitalRead(button_pin) == HIGH)
  {
    start_button_press = millis();
    // wait till button is let go
    while (digitalRead(button_pin))
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


void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  BUTTON_STATE = is_button_pressed(BUTTON_PIN, BUTTON_PRESS_THRESHOLD, START_BUTTON_PRESS);
  Serial.println(BUTTON_STATE);

}
