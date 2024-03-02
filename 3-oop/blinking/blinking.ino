#include "src/Led.h"

#define LED_PIN 8

Light *light;

void setup()
{
  light = new Led(LED_PIN);
}

void loop()
{
  light->switchOn();
  delay(500);
  light->switchOff();
  delay(500);
};
