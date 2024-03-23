/*
 * Pattern observer example.
 */
#include "src/ButtonCounter.h"
#include "src/ButtonImpl.h"

AbstractButton *buttonA, *buttonB;
ButtonCounter *listener;

void setup() {
    Serial.begin(9600);
    buttonA = new ButtonImpl(2);
    buttonB = new ButtonImpl(3);
    listener = new ButtonCounter();
    buttonA->addListener(listener);
    buttonB->addListener(listener);
}

void loop() {
    Serial.println(listener->getCount());
};
