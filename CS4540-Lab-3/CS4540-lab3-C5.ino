void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(LED_BUILTIN, OUTPUT); // Set LED pin as output
  Serial.println("Send '1' to turn LED ON, or '0' for OFF:");
}

void loop() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read(); // Read incoming byte

    if (incomingByte == '1') {
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
      Serial.println("LED ON");
    } else if (incomingByte == '0') {
      digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
      Serial.println("LED OFF");
    } else {
      Serial.print("");
      Serial.println(incomingByte);
    }
  }
}