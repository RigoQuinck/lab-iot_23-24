

void setup()
{
  Serial.begin(115200);
  Serial.flush();
  Serial.println("READY");
}

void loop()
{
  if (Serial.available())
  {
    char data = Serial.read();
    // Serial.print(data);
  }
}
