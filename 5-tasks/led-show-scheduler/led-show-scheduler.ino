#include "src/Scheduler.h"
#include "src/BlinkTask.h"
#include "src/AlternateLedsTask.h"

#define BLINK_LED_PIN 13
#define ALT_LED_1_PIN 4
#define ALT_LED_2_PIN 7
#define ALT_LED_3_PIN 8
#define SCHED_PERIOD 50
#define BLINK_PERIOD 500
#define ALT_PERIOD 500

Scheduler sched;

void setup()
{
  sched.init(SCHED_PERIOD);

  Task *blinkTask = new BlinkTask(BLINK_LED_PIN);
  blinkTask->init(BLINK_PERIOD);
  sched.addTask(blinkTask);

  Task *alternateLedsTask = new AlternateLedsTask(ALT_LED_1_PIN, ALT_LED_2_PIN, ALT_LED_3_PIN);
  alternateLedsTask->init(ALT_PERIOD);
  sched.addTask(alternateLedsTask);
}

void loop()
{
  sched.schedule();
}
