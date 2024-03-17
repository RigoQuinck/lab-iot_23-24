#include "src/Scheduler.h"
#include "src/BlinkTask.h"
#include "src/PrintTask.h"

#define BLINK_PIN 8

#define SCHED_PERIOD 50
#define BLINK_PERIOD 150
#define PRINT_PERIOD 500

Scheduler sched;

void setup()
{
  Serial.begin(9600);
  sched.init(SCHED_PERIOD);

  Task *t0 = new BlinkTask(BLINK_PIN);
  t0->init(BLINK_PERIOD);

  Task *t1 = new PrintTask();
  t1->init(PRINT_PERIOD);

  sched.addTask(t0);
  sched.addTask(t1);
}

void loop()
{
  sched.schedule();
}
