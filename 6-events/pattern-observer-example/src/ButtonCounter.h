#include "Button.h"

class ButtonCounter : public ButtonListener {
   private:
    volatile int count;

   public:
    ButtonCounter();

    void notifyButtonPressed();

    void notifyButtonReleased();

    int getCount();
};