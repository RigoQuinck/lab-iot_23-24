#ifndef __ASYNC_FSM__
#define __ASYNC_FSM__

#define MAX_EVQUEUE_SIZE 20
#define NUM_PINS 13

/**
 * Class representing an event
 */
class Event {
   public:
    Event(int type);
    int getType();

   private:
    int type;
};

/**
 * Class representing event observers, observing Event.
 */
class Observer {
   public:
    virtual void notifyEvent(Event* ev) = 0;
};

/**
 * Base class representing an event source, generating Event
 * observed by an Observer.
 */
class EventSource {
   public:
    void registerObserver(Observer* observer);

    /* called by the interrupt dispatcher to notify a new event */
    virtual void notifyInterrupt(int pin) = 0;

   protected:
    void bindInterrupt(int pin);

    /* called by to generate an event to be observed by the observer */
    void generateEvent(Event* ev);

    Observer* observer;
};

/**
 * Class binding interrupts to event sources
 */
class InterruptDispatcher {
   public:
    InterruptDispatcher();
    void bind(int pin, EventSource* src);
    void notifyInterrupt(int pin);

   private:
    EventSource* sourceRegisteredOnPin[NUM_PINS];
    void (*notifyFunctions[NUM_PINS])() = {};

    static void notifyInterrupt_0();
    static void notifyInterrupt_1();
    static void notifyInterrupt_2();
    static void notifyInterrupt_3();
    static void notifyInterrupt_4();
    static void notifyInterrupt_5();
    static void notifyInterrupt_6();
    static void notifyInterrupt_7();
    static void notifyInterrupt_8();
    static void notifyInterrupt_9();
    static void notifyInterrupt_10();
    static void notifyInterrupt_11();
    static void notifyInterrupt_12();
    static void notifyInterrupt_13();
};

/**
 * Class representing an event queue, used inside the async FSM
 */
class EventQueue {
   public:
    EventQueue();
    bool isEmpty();
    void enqueue(Event* ev);
    Event* dequeue();

   private:
    Event* queue[MAX_EVQUEUE_SIZE];
    int head, tail;
};

/**
 * Base abstract class for implementing asynchronous
 * Finite State Machines.
 *
 * NOTES:
 * - it is an Observer of events generated by event source
 * - the state is meant to be modelled by derived classes
 */
class AsyncFSM : public Observer {
   public:
    virtual void handleEvent(Event* ev) = 0;
    void notifyEvent(Event* ev);
    void checkEvents();

   protected:
    AsyncFSM();
    EventQueue eventQueue;
};

#endif
