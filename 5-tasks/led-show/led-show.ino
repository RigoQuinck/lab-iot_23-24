#include "src/BlinkTask.h"
#include "src/AlternateLedsTask.h"
#include "src/Timer.h"

Timer timer;

BlinkTask blinkTask(13);
AlternateLedsTask alternateLedsTask(4, 7, 8);

void setup()
{
  blinkTask.init();
  alternateLedsTask.init();
  timer.setupPeriod(500);
}

void loop()
{
  timer.waitForNextTick();
  blinkTask.tick();
  alternateLedsTask.tick();
}
