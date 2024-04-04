#include "WindTask.h"

#include "WindSensorImpl.h"

#define ALERT_WIND_SPEED 30
#define IDLE_WIND_SPEED 25
#define SERVO_UP 0

WindTask::WindTask(WindSensor *windSensor) {
    this->windSensor = windSensor;
    state = IDLE;
}

void WindTask::init(int period) {
    Task::init(period);
    state = IDLE;
}

void WindTask::tick() {
    switch (state) {
        case IDLE:
            idle();
            break;
        case ALERT:
            alert();
            break;
    }
}

void WindTask::idle() {
    int windSpeed = this->windSensor->getWindSpeed();

    if (windSpeed >= ALERT_WIND_SPEED) {
        state = ALERT;
    }
}

void WindTask::alert() {
    int windSpeed = this->windSensor->getWindSpeed();
    if (windSpeed <= IDLE_WIND_SPEED) {
        state = IDLE;
    }
}

WindTaskState WindTask::getState() {
    return this->state;
}