#include "Arduino.h"
#include "LightSensorImpl.h"

// These constants should match the photoresistor's "gamma" and "rl10" attributes
const float GAMMA = 0.7;
const float RL10 = 50;

LightSensorImpl::LightSensorImpl(int pin) {
    this->pin = pin;
}

int LightSensorImpl::getLightIntensity() {
    int value = analogRead(this->pin);
    float lux = this->analogValueToLux(value);
    return (int)lux;
}

float LightSensorImpl::analogValueToLux(int value) {
    float voltage = value / 1024. * 5;
    float resistance = 2000 * voltage / (1 - voltage / 5);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
}
