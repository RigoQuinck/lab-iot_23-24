#include "DoorTask.h"

#define OPENED_ANGLE 180
#define CLOSED_ANGLE 0
#define STEP 10
#define OPENED_PERIOD 10000

DoorTask::DoorTask(Presence* presence, MyServo* myservo, AlertTask* alertTask) {
    this->presence = presence;
    this->myservo = myservo;
    this->alertTask = alertTask;
    state = CLOSED;
    openedTimeElapsed = 0;
}

void DoorTask::tick() {
    switch (state) {
        case CLOSED:
            closed();
            break;
        case OPENING:
            opening();
            break;
        case OPENED:
            opened();
            break;
        case CLOSING:
            closing();
            break;
    }
}

void DoorTask::closed() {
    if (alertTask->getState() != AlertTaskState::ALERT && presence->isPresent()) {
        state = OPENING;
    }
}

void DoorTask::opening() {
    if (alertTask->getState() == AlertTaskState::ALERT) {
        state = CLOSING;
    }

    int curr = myservo->getAngle();
    int newPos = curr + STEP;
    myservo->setAngle(newPos);

    if (newPos == OPENED_ANGLE) {
        openedTimeElapsed = 0;
        state = OPENED;
    }
}

void DoorTask::closing() {
    int curr = myservo->getAngle();
    int newPos = curr - STEP;
    myservo->setAngle(newPos);

    if (newPos == CLOSED_ANGLE) {
        state = CLOSED;
    }
}

void DoorTask::opened() {
    if (alertTask->getState() == AlertTaskState::ALERT) {
        state = CLOSING;
    }
    openedTimeElapsed += this->taskPeriod;
    if (openedTimeElapsed >= OPENED_PERIOD) {
        state = CLOSING;
    }
}