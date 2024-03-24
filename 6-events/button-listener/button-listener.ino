#include "src/ButtonCounter.h"
#include "src/ButtonImpl.h"

ButtonEventSource *buttonA, *buttonB;
ButtonCounter *listener;

int lastCount = NULL;

void setup() {
    Serial.begin(9600);
    buttonA = new ButtonImpl(2);
    buttonB = new ButtonImpl(3);
    listener = new ButtonCounter();
    buttonA->addListener(listener);
    buttonB->addListener(listener);
    lastCount = listener->getCount();
    printCount(lastCount);
}

void loop() {
    int count = listener->getCount();
    if (lastCount != count) {
        printCount(count);
        lastCount = count;
    }
};

void printCount(int count) {
    Serial.println(String("Event count ") + count);
    Serial.println(String("Pressed count ") + listener->getPressedCount());
    Serial.println(String("Released count ") + listener->getReleasedCount());
}