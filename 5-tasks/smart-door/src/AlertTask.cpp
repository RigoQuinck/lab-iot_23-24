#include "AlertTask.h"

#define ALERT_TEMP 40

AlertTask::AlertTask(TemperatureSensor *tempSensor, Light *light) {
    state = IDLE;
    this->tempSensor = tempSensor;
    this->light = light;
}

void AlertTask::tick() {
    switch (state) {
        case IDLE:
            idle();
            break;
        case ALERT:
            alert();
            break;
    }
}

void AlertTask::idle() {
    float temp = tempSensor->getTemperature();
    if (temp >= ALERT_TEMP) {
        light->switchOn();
        state = ALERT;
    }
}

void AlertTask::alert() {
    float temp = tempSensor->getTemperature();
    if (temp < ALERT_TEMP) {
        light->switchOff();
        state = IDLE;
    }
}

AlertTaskState AlertTask::getState() {
    return state;
}