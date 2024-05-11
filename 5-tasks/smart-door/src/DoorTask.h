#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include "AlertTask.h"
#include "MyServo.h"
#include "Presence.h"
#include "Task.h"

typedef enum { CLOSED, OPENING, OPENED, CLOSING } DoorTaskState;

class DoorTask : public Task {
   public:
    DoorTask(Presence* presence, MyServo* myservo, AlertTask* alertTask);
    void tick();

   private:
    Presence* presence;
    MyServo* myservo;
    AlertTask* alertTask;
    int openedTimeElapsed;

    DoorTaskState state;

    void closed();
    void opening();
    void opened();
    void closing();
};

#endif