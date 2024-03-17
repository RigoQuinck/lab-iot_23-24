#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

class Task
{
  int taskPeriod;
  int timeElapsed;

public:
  virtual void init(int period)
  {
    taskPeriod = period;
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod)
  {
    timeElapsed += basePeriod;
    if (timeElapsed >= taskPeriod)
    {
      timeElapsed = 0;
      return true;
    }
    else
    {
      return false;
    }
  }
};

#endif
