void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
}
void loop() {
  digitalWrite(13, digitalRead(A0));
  digitalWrite(11, digitalRead(A1));
  digitalWrite(8, digitalRead(A2));
}