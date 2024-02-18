#define BUTTON_PIN 2

volatile int count = 0;
int prev = 0;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), inc, RISING);
}

void loop()
{
  if (count != prev)
  {
    Serial.println(count);
    prev = count;
  }
}

void inc()
{
  count++;
}
