#include "Button.h"
#include "Light.h"
#include "async_fsm.h"
#include "console.h"

// 1: Conta gli eventi di pressione e rilascio di un botton
// 2: Ogni 10 eventi mostro il conteggio
// 3: Bottone che fa da switch per contare o fermate il conteggio

class ButtonCounterAsyncFSM : public AsyncFSM {
   public:
    ButtonCounterAsyncFSM(Button* btn, Button* button2, Light* light, Console* console);
    void handleEvent(Event* ev);

   private:
    Button* btn;
    Button* button2;
    Light* light;
    Console* console;
    int pressedCount;
    int releasedCount;
    enum { IDLE, SHOW } state;
};