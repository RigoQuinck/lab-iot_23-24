#include "ShadowTask.h"

#include "LightSensorImpl.h"
#include "Motor.h"
#include "TemperatureSensorImpl.h"

#define SERVO_UP 0
#define SERVO_DOWN 180
#define SERVO_STEP 5
#define UP_DIRECTION -1
#define DOWN_DIRECTION 1
#define GO_DOWN_LUX 10000
#define GO_DOWN_TEMP 28
#define GO_UP_LUX 400

ShadowTask::ShadowTask(LightSensor *lightSensor, TemperatureSensor *tempSensor, MyServo *servo, WindTask *windTask) {
    this->lightSensor = lightSensor;
    this->tempSensor = tempSensor;
    this->servo = servo;
    this->windTask = windTask;
    state = UP;
}

void ShadowTask::init(int period) {
    Task::init(period);
    servo->setAngle(SERVO_UP);
    state = UP;
}

// Quando la luminosità raggiunge 10000 e la temperatura esterna è più alta di 28 gradi, abbasso il tendone.
// Quando la limunosità cala raggiunge 400 alzo il tendone.
void ShadowTask::tick() {
    switch (state) {
        case UP:
            up();
            break;
        case DOWN:
            down();
            break;
        case MOVING:
            moving();
            break;
    }
}

void ShadowTask::up() {
    if (this->windTask->getState() != ALERT) {
        int lux = this->lightSensor->getLightIntensity();
        double temp = this->tempSensor->getTemperature();

        if (lux >= GO_DOWN_LUX && temp >= GO_DOWN_TEMP) {
            direction = DOWN_DIRECTION;
            state = MOVING;
        }
    }
}

void ShadowTask::down() {
    int lux = this->lightSensor->getLightIntensity();
    WindTaskState windState = this->windTask->getState();

    if (windState == WindTaskState::ALERT || lux <= GO_UP_LUX) {
        direction = UP_DIRECTION;
        state = MOVING;
    }
}

void ShadowTask::moving() {
    if (this->windTask->getState() == WindTaskState::ALERT) {
        direction = UP_DIRECTION;
    }
    int curr = servo->getAngle();
    int newPos = curr + SERVO_STEP * direction;
    servo->setAngle(newPos);
    if (newPos == SERVO_DOWN) {
        state = DOWN;
    }
    if (newPos == SERVO_UP) {
        state = UP;
    }
}