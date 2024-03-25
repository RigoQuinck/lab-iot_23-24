/*
- Quando la luminosità è buona e la temperatura esterna è più alta di 28 gradi, abbasso il tendone.
- Quando il vento (simulato da un potenziometro) supera i 30 kmh allora devo tirare su il tendone
  e non può più essere abbassato fino a chè non scende sotto i 25 kmh.

  https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
  https://docs.wokwi.com/parts/wokwi-servo
  https://docs.wokwi.com/parts/wokwi-potentiometer
 */

#include "src/Scheduler.h"
#include "src/ShadowTask.h"

#define LIGHT_SENSOR_PIN A0
#define TEMP_PIN A4
#define SERVO_PIN 5
#define POT_PIN A1

#define SHADOW_TASK_PERIOD 50
#define SCHED_PERIOD 50

Scheduler sched;

void setup() {
    Serial.begin(9600);

    ShadowTask *shadowTask = new ShadowTask(TEMP_PIN, LIGHT_SENSOR_PIN, SERVO_PIN);
    shadowTask->init(SHADOW_TASK_PERIOD);

    sched.init(SCHED_PERIOD);
    sched.addTask(shadowTask);
}

void loop() {
    sched.schedule();
}