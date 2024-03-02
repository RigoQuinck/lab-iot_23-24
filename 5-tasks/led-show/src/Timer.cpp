#include "Timer.h"
#include <TimerOne.h>

volatile bool timerFlag = false;

void timerHandler()
{
  timerFlag = true;
}

Timer::Timer()
{
  timerFlag = false;
  Timer1.detachInterrupt();
}

/* period in ms */
void Timer::setupPeriod(int period)
{
  Timer1.initialize(period * 1000L);
  Timer1.attachInterrupt(timerHandler);
}

void Timer::waitForNextTick()
{
  while (!timerFlag)
  {
  }
  timerFlag = false;
}
