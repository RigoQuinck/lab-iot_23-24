#include <TimerOne.h>

#define LED_PIN 8
#define PERIOD_uS 1000000

boolean flagState = false;

void blink()
{
  if (!flagState)
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("ON");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("OFF");
  }
  flagState = !flagState;
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Timer1.initialize(PERIOD_uS);
  Timer1.attachInterrupt(blink);
  Serial.begin(9600);
}

void loop()
{
}
