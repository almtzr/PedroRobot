bool state = false;
void setup() {
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  if (digitalRead(A0) == HIGH) {
    state = !state;
    digitalWrite(13, state);
    delay(300);
  }
}