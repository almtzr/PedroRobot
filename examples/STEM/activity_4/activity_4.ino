void setup() {
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  if (digitalRead(A0) == HIGH) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}