#include "src/BlinkTask.h"
#include "src/AlternateLedsTask.h"
#include "src/Timer.h"

#define BLINK_LED_PIN 13
#define ALT_LED_1_PIN 4
#define ALT_LED_2_PIN 7
#define ALT_LED_3_PIN 8

Timer timer;

BlinkTask blinkTask(BLINK_LED_PIN);
AlternateLedsTask alternateLedsTask(ALT_LED_1_PIN, ALT_LED_2_PIN, ALT_LED_3_PIN);

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
