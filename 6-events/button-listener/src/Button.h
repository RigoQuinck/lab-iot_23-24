#ifndef __BUTTON__
#define __BUTTON__

#include "event.h"

#define MAX_BUTTON_LISTENERS 5

/*
 * Button interface
 */
class Button {
   public:
    virtual bool isPressed() = 0;
};

/*
 * Interface of listeners that are notified
 * when a button generate an event
 */
class ButtonListener {
   public:
    virtual void notifyButtonPressed() = 0;
    virtual void notifyButtonReleased() = 0;
};

/*
 * The base class for buttons generating events
 * [abstract class]
 */
class ButtonEventSource : public EventSource, public Button {
   public:
    /* to add a new listener */
    bool addListener(ButtonListener* listener);

   protected:
    ButtonEventSource();

    int nListeners;
    ButtonListener* listeners[MAX_BUTTON_LISTENERS];
};
#endif
