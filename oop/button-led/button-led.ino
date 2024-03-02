#include "src/Led.h"
#include "src/ButtonImpl.h"

#define LED_PIN 13
#define BUTTON_PIN 2

Light *light;
Button *button;

boolean lightOn;

void setup()
{
    light = new Led(LED_PIN);
    button = new ButtonImpl(BUTTON_PIN);
    lightOn = false;
}

void loop()
{
    bool isPressed = button->isPressed();

    if (!lightOn && isPressed)
    {
        light->switchOn();
        lightOn = true;
    }
    else if (lightOn && !isPressed)
    {
        light->switchOff();
        lightOn = false;
    }
}
