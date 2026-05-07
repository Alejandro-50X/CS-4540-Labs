// the pins for button and led
#define LED_PIN 8
#define BUTTON_PIN 7

void setup(){

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

}

void loop(){

  // when the button is pressed the led is off
  if (digitalRead(BUTTON_PIN) == HIGH){
    digitalWrite(LED_PIN, LOW);
  }
  // when the button is not pressed the led will be on
  else {
    digitalWrite(LED_PIN, HIGH);
  }
}