#include "ButtonCounter.h"

#include "Arduino.h"

ButtonCounter::ButtonCounter() {
    count = 0;
}

void ButtonCounter::notifyButtonPressed() {
    count++;
}

void ButtonCounter::notifyButtonReleased() {
    count++;
}

int ButtonCounter::getCount() {
    noInterrupts();
    int c = count;
    interrupts();
    return c;
}