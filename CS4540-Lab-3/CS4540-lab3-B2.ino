int ledPin[] = {6, 7, 8, 9}; // the pins on the baord
int count = 0;
int direction = 1; // determines if we are counting up or down

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPin[i], OUTPUT); 
  }

}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(ledPin[i], bitRead(count, i));
  }

  // the counter for determining if we are going up or down
  count += direction;

  // when we are at 0 or 15 we go to the opposite direction 
  if (count >= 15 || count <= 0) {
    direction = -direction;
  }

  delay(500);
}