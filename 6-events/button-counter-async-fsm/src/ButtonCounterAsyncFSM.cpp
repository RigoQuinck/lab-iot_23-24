#include "ButtonCounterAsyncFSM.h"

ButtonCounterAsyncFSM::ButtonCounterAsyncFSM(Button* btn, Button* button2, Light* light, Console* console) {
    this->btn = btn;
    this->console = console;
    this->button2 = button2;
    this->light = light;
    pressedCount = 0;
    releasedCount = 0;
    state = SHOW;
    btn->registerObserver(this);
    button2->registerObserver(this);
}

void ButtonCounterAsyncFSM::handleEvent(Event* ev) {
    switch (ev->getType()) {
        case BUTTON_PRESSED_EVENT:
            Button* btnev = ((ButtonPressed*)ev)->getSource();
            EventSource* src = ev->getSource();
            pressedCount++;
            break;
        case BUTTON_RELEASED_EVENT:
            releasedCount++;
            break;
    }

    switch (state) {
        case IDLE:
            if (((pressedCount + releasedCount) % 10) == 0) {
                state = SHOW;
            }
            break;
        case SHOW:
            console->log(pressedCount + releasedCount);
            state = IDLE;
            break;
    }
}