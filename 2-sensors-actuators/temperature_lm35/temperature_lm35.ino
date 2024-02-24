void setup()
{
  Serial.begin(9600);
  Serial.flush();
}

void loop()
{
  int value = analogRead(A2);

  /* value : 1023 = mV : 5000 */
  /* mV = 5000 * value / 1023 */

  int mV = 5000 * value / 1023;

  /* clesius = mV / 10 (since we have 10 mV => 1 °C ) */

  double clesius = mV * 0.1;

  Serial.println(String("Value in C: ") + clesius);

  delay(1000);
}
