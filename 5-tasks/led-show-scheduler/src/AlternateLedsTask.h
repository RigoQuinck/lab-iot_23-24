#include "Task.h"
#include "Led.h"

#define N_LIGHTS 3

class AlternateLedsTask : public Task
{
    int pin[N_LIGHTS];
    Light *lights[N_LIGHTS];
    int state;

public:
    AlternateLedsTask(int pin0, int pin1, int pin3);
    void init(int period);
    void tick();
};