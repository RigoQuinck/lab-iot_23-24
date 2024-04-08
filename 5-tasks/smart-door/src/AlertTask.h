#ifndef __ALERT_TASK__
#define __ALERT_TASK__

#include "Light.h"
#include "Task.h"
#include "TemperatureSensor.h"

typedef enum { IDLE, ALERT } AlertTaskState;

class AlertTask : public Task {
   public:
    AlertTask(TemperatureSensor *tempSensor, Light *light);
    AlertTaskState getState();
    void tick();

   private:
    AlertTaskState state;
    TemperatureSensor *tempSensor;
    Light *light;

    void idle();
    void alert();
};

#endif