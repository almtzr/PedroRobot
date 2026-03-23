int step = 0;
void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  if (digitalRead(A0) == HIGH && step == 0) {
    step = 1; delay(300);
  }
  if (digitalRead(A1) == HIGH && step == 1) {
    step = 2; delay(300);
  }
  if (digitalRead(A2) == HIGH && step == 2) {
    digitalWrite(13, HIGH);
  }
}