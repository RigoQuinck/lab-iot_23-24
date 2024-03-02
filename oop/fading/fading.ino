#include "src/LedExt.h"

// the pin must by a PWM one
#define LED_PIN 10

LightExt *light;
int brightness;
int fadeAmount;

void setup()
{
  brightness = 0;
  fadeAmount = 5;
  light = new LedExt(LED_PIN, brightness);
  light->switchOn();
}

void loop()
{
  light->setIntensity(brightness);
  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255)
  {
    fadeAmount = -fadeAmount;
  }
  delay(50);
};
