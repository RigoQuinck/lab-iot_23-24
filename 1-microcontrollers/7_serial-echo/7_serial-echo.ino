

void setup()
{
  Serial.begin(115200);
  Serial.flush();
}

void loop()
{
  if (Serial.available())
  {
    char data = Serial.read();
    Serial.print(data);
  }
}
