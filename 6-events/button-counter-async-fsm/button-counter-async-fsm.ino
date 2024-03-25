#include "src/ButtonCounterAsyncFSM.h"
#include "src/Led.h"
#include "src/async_fsm.h"
#include "src/buttonImpl.h"
#include "src/console.h"

#define BUTTON_PIN 2
#define LED_PIN 2
#define BTN_2_PIN 2

ButtonCounterAsyncFSM* btnCounter;

void setup() {
    Button* button = new ButtonImpl(BUTTON_PIN);
    Button* button2 = new ButtonImpl(BTN_2_PIN);
    Light* light = new Led(LED_PIN);
    Console* console = new Console();
    btnCounter = new ButtonCounterAsyncFSM(button, button2, light, console);
}

void loop() {
    btnCounter->checkEvents();
}
