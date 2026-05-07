// the pins for the led and the button
#define LED_PIN 8
#define BUTTON_PIN 7

void setup(){

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

}

void loop(){

  // when the button is pressed the led will turn on
  if (digitalRead(BUTTON_PIN) == HIGH){
    digitalWrite(LED_PIN, HIGH);
  }
  // when the button is not pressed the led will be off
  else {
    digitalWrite(LED_PIN, LOW);
  }
}