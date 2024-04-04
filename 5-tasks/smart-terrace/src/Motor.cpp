#include "Motor.h"

#include "Arduino.h"

Motor::Motor(int pin) {
    this->pin = pin;
    this->pos = 0;
    this->servo.attach(pin);
}

void Motor::setAngle(int newPos) {
    pos = newPos;
    servo.write(mapPos(pos));
}

void Motor::forward() {
    pos = pos < 180 ? ++pos : pos;
    servo.write(mapPos(pos));
};

void Motor::backward() {
    pos = pos > 0 ? --pos : pos;
    servo.write(mapPos(pos));
}

int Motor::getAngle() {
    return pos;
};

int Motor::mapPos(int pos) {
    return map(pos, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}
