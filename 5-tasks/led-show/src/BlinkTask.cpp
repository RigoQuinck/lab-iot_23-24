#include "BlinkTask.h"

BlinkTask::BlinkTask(int pin) {
    this->pin = pin;
}

void BlinkTask::init() {
    light = new Led(pin);
    state = OFF;
}

void BlinkTask::tick() {
    switch (state) {
        case OFF:
            light->switchOn();
            state = ON;
            break;
        case ON:
            light->switchOff();
            state = OFF;
            break;
    }
}
