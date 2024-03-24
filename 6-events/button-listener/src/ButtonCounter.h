#include "Button.h"

class ButtonCounter : public ButtonListener {
   private:
    volatile int pressedCount;
    volatile int releasedCount;

   public:
    ButtonCounter();

    /*
     * Get events count
     */
    int getCount();
    /*
     * Get pressed events count
     */
    int getPressedCount();
    /*
     * Get released events count
     */
    int getReleasedCount();

    /*
     * ButtonListener methods
     */
    void notifyButtonPressed();
    void notifyButtonReleased();
};