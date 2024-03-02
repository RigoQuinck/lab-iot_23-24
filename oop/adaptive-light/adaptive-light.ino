#include "src/LedExt.h"
#include "src/LightSensorImpl.h"

// the pin must by a PWM one
#define LED_PIN 10
#define LED_SENSOR_PIN A0

LightExt *led;
LightSensor *lightSensor;

void setup()
{
  led = new LedExt(LED_PIN, 0);
  led->switchOn();
  lightSensor = new LightSensorImpl(LED_SENSOR_PIN);
  Serial.begin(9600);
}

void loop()
{
  int level = lightSensor->getLightIntensity();
  Serial.println(level);
  if (level < 0)
  {
    level = 0;
  }
  else if (level > 255)
  {
    level = 255;
  }
  led->setIntensity(255 - level);
};
