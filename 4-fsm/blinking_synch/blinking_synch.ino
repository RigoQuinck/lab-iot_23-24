#include "src/Led.h"
#include "src/Timer.h"

#define LED_PIN 8

Light *light;
Timer timer;

enum { ON, OFF } state;

void setup() {
    Serial.begin(9600);
    light = new Led(LED_PIN);
    state = OFF;
    timer.setupPeriod(500);
}

void step() {
    switch (state) {
        case OFF:
            light->switchOn();
            Serial.println("ON");
            state = ON;
            break;
        case ON:
            light->switchOff();
            Serial.println("OFF");
            state = OFF;
            break;
    }
}

void loop() {
    timer.waitForNextTick();
    step();
};
