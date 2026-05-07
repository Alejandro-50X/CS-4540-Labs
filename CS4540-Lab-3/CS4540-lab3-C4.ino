
void setup() {
  Serial.begin(9600);
  delay(500);              // give Serial Monitor time to connect
  randomSeed(analogRead(0));
}

String catFacePic =
  "  |\---/|  '\n"
  "  | o_o | \n"
  "   \_^_/ \n";

String owlPic =
  "  /\\_/\\\n"
  " ( o o )\n"
  " /  V  \\\n"
  "/(  _  )\\\n";

void loop() {
  for (int i = 0; i < 3; i++) {
    int choice = random(0, 2);

    if (choice == 0) {
      Serial.print(catFacePic);
    } else {
      Serial.print(owlPic);
    }

    Serial.println();   // blank line between prints
    delay(1000);
  }

  while (true) {
  }
}