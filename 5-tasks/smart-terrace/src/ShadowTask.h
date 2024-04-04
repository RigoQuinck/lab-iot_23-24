#ifndef __SHADOW_TASK__
#define __SHADOW_TASK__

#include "LightSensor.h"
#include "MyServo.h"
#include "Task.h"
#include "TemperatureSensor.h"
#include "WindTask.h"

class ShadowTask : public Task {
   public:
    ShadowTask(LightSensor *lightSensor, TemperatureSensor *tempSensor, MyServo *servo, WindTask *windTask);
    void init(int period);
    void tick();

   private:
    LightSensor *lightSensor;
    TemperatureSensor *tempSensor;
    MyServo *servo;
    WindTask *windTask;
    enum { DOWN, UP, MOVING } state;
    int direction;

    void up();
    void down();
    void moving();
};

#endif