#include "Button.h"

ButtonEventSource::ButtonEventSource() {
    nListeners = 0;
}

bool ButtonEventSource::addListener(ButtonListener* listener) {
    if (nListeners < MAX_BUTTON_LISTENERS) {
        listeners[nListeners++] = listener;
        return true;
    } else {
        return false;
    }
}