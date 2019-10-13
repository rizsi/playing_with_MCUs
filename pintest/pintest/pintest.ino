// Mini program that toggles each pins to measure if one pin is broken. Requred by life.

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  for(uint8_t i=2;i<13;++i)
  {
    pinMode(i, OUTPUT);
  }
}
void writeAll(uint8_t value)
{
  digitalWrite(A0, value);
  digitalWrite(A2, value);
  digitalWrite(A3, value);
  digitalWrite(A4, value);
  for(uint8_t i=2;i<=13;++i)
  {
    digitalWrite(i, value);
  }
  
}


void loop() {
  delay(500);
  writeAll(HIGH);
  delay(500);
  writeAll(LOW);
}
