int leds[] = {13, 11, 8, 7};
void setup() {
  for(int i=0; i<4; i++){
    pinMode(leds[i], OUTPUT);
  }
}
void loop() {
  for(int i=0; i<4; i++){
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }
}