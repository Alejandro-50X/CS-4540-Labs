// the pin numbers for the led and button
#define LED_PIN 8
#define BUTTON_PIN 7

bool ledState = false;
bool lastButtonState = false; 

void setup(){

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

}

void loop(){

  // checks if button is pressed 
  bool currentButton = digitalRead(BUTTON_PIN);

  // checks if the button is presesed and was also not pressed at the last cycle
  if (currentButton == HIGH && lastButtonState == LOW) {
    // flips the led state between true and flase to determine if the led should be on or off
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  }

  //svae the led state
  lastButtonState = currentButton;
  delay(50); // try to stop debounce to prevent presses to cause multiple blinks

}