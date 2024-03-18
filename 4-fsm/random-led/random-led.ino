#include "src/ButtonImpl.h"
#include "src/Led.h"

#define LED_NUM 3
#define LED_1 7
#define LED_2 8
#define LED_3 9
#define BTN 10
#define WAIT_MS 1000

enum { ON, OFF, WAIT } state;

Button *btn;
Light *leds[LED_NUM] = {};

long ledOn;
long prevTs = millis();

void setup() {
    randomSeed(analogRead(0));

    leds[0] = new Led(LED_1);
    leds[1] = new Led(LED_2);
    leds[2] = new Led(LED_3);
    btn = new ButtonImpl(BTN);

    state = OFF;
}

void loop() {
    step();
}

void step() {
    switch (state) {
        case ON:
            on();
            break;
        case OFF:
            off();
            break;
        case WAIT:
            wait();
            break;
    }
}

void on() {
    if (btn->isPressed()) {
        leds[ledOn]->switchOff();
        state = WAIT;
    }
}

void off() {
    ledOn = random(LED_NUM);
    leds[ledOn]->switchOn();
    state = ON;
}

void wait() {
    long ts = millis();
    if (ts - prevTs >= WAIT_MS) {
        state = OFF;
    }
}