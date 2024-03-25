#include "Arduino.h"
#include "LightSensorImpl.h"

// These constants should match the photoresistor's "gamma" and "rl10" attributes
const float GAMMA = 0.7;
const float RL10 = 50;

LightSensorImpl::LightSensorImpl(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

int LightSensorImpl::getLightIntensity() {
    int value = analogRead(this->pin);
    double lux = this->analogValueToLux(value);
    return (int)lux;
}

double LightSensorImpl::analogValueToLux(int value) {
    double voltage = value / 1024. * 5;
    double resistance = 2000 * voltage / (1 - voltage / 5);
    double lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
    return lux;
}
