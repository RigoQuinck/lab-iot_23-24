#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "Led.h"

class BlinkTask : public Task
{

  int pin;
  Light *light;

  enum
  {
    ON,
    OFF
  } state;

public:
  BlinkTask(int pin);
  void init();
  void tick();
};

#endif
