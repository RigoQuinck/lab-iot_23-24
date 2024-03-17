#include "PrintTask.h"
#include "Arduino.h"

void PrintTask::init(int period)
{
  Task::init(period);
  count = 0;
}

void PrintTask::tick()
{
  count++;
  Serial.println("count " + String(count) + " millis: " + String(millis()));
}
