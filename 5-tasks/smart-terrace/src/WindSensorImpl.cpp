#include "WindSensorImpl.h"

#include "Arduino.h"

WindSensorImpl::WindSensorImpl(int pin) {
    this->pin = pin;
}

float WindSensorImpl::getWindSpeed() {
    int value = analogRead(this->pin);
    return map(value, 0, 1023, 0, 150);  // maps value to wind kmh
}