#include "AlternateLedsTask.h"

AlternateLedsTask::AlternateLedsTask(int pin0, int pin1, int pin3) {
    this->pin[0] = pin0;
    this->pin[1] = pin1;
    this->pin[2] = pin3;
}

void AlternateLedsTask::init() {
    for (int i = 0; i < N_LIGHTS; i++) {
        lights[i] = new Led(pin[i]);
    }
    state = 0;
}

void AlternateLedsTask::tick() {
    lights[state]->switchOff();
    state = (state + 1) % N_LIGHTS;
    lights[state]->switchOn();
}
