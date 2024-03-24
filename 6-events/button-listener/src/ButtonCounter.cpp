#include "ButtonCounter.h"

#include "Arduino.h"

ButtonCounter::ButtonCounter() {
    pressedCount = 0;
    releasedCount = 0;
}

void ButtonCounter::notifyButtonPressed() {
    pressedCount++;
}

void ButtonCounter::notifyButtonReleased() {
    releasedCount++;
}

int ButtonCounter::getCount() {
    noInterrupts();
    int c = pressedCount + releasedCount;
    interrupts();
    return c;
}

int ButtonCounter::getPressedCount() {
    noInterrupts();
    int c = pressedCount;
    interrupts();
    return c;
}

int ButtonCounter::getReleasedCount() {
    noInterrupts();
    int c = releasedCount;
    interrupts();
    return c;
}