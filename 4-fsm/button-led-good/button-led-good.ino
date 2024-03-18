#include "src/Led.h"
#include "src/Timer.h"
#include "src/ButtonImpl.h"

#define LED_PIN 13
#define BUTTON_PIN 2

Light *light;
Button *button;
Timer timer;

enum
{
  ON,
  OFF
} state;

void setup()
{
  Serial.begin(9600);
  light = new Led(LED_PIN);
  button = new ButtonImpl(BUTTON_PIN);
  state = OFF;
  timer.setupPeriod(50);
}

void step()
{
  bool isPressed = button->isPressed();
  switch (state)
  {
  case OFF:
    if (isPressed)
    {
      light->switchOn();
      Serial.println("ON");
      state = ON;
    }
    break;
  case ON:
    if (!isPressed)
    {
      light->switchOff();
      Serial.println("OFF");
      state = OFF;
    }
    break;
  }
}

void loop()
{
  timer.waitForNextTick();
  step();
};
