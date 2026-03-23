void setup() {
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
}
void loop() {
  delay(random(1000,3000));
  digitalWrite(13, HIGH);
  while(digitalRead(A0) == LOW);
  digitalWrite(13, LOW);
}