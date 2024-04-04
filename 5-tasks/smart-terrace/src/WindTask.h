#ifndef __WIND_TASK__
#define __WIND_TASK__

#include "Task.h"
#include "WindSensor.h"

typedef enum { IDLE, ALERT } WindTaskState;

class WindTask : public Task {
   public:
    WindTask(WindSensor *windSensor);
    void init(int period);
    void tick();
    WindTaskState getState();

   private:
    WindSensor *windSensor;
    WindTaskState state;

    void idle();
    void alert();
};

#endif