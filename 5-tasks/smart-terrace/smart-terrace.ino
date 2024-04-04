/*
- Quando la luminosità è buona e la temperatura esterna è più alta di 28 gradi, abbasso il tendone.
- Quando il vento (simulato da un potenziometro) supera i 30 kmh allora devo tirare su il tendone
  e non può più essere abbassato fino a chè non scende sotto i 25 kmh.

  https://docs.wokwi.com/parts/wokwi-photoresistor-sensor
  https://docs.wokwi.com/parts/wokwi-servo
  https://docs.wokwi.com/parts/wokwi-potentiometer
 */

#include "src/LightSensorImpl.h"
#include "src/Motor.h"
#include "src/Scheduler.h"
#include "src/ShadowTask.h"
#include "src/TemperatureSensorImpl.h"
#include "src/WindSensorImpl.h"
#include "src/WindTask.h"

#define LIGHT_SENSOR_PIN A0
#define TEMP_PIN A4
#define SERVO_PIN 9
#define WIND_PIN A1

#define SHADOW_TASK_PERIOD 50
#define WIND_TASK_PERIOD 1000
#define SCHED_PERIOD 50

Scheduler sched;

void setup() {
    WindSensor *windSensor = new WindSensorImpl(WIND_PIN);
    WindTask *windTask = new WindTask(windSensor);
    windTask->init(WIND_TASK_PERIOD);

    LightSensor *lightSensor = new LightSensorImpl(LIGHT_SENSOR_PIN);
    TemperatureSensor *tempSensor = new TemperatureSensorImpl(TEMP_PIN);
    MyServo *servo = new Motor(SERVO_PIN);
    ShadowTask *shadowTask = new ShadowTask(lightSensor, tempSensor, servo, windTask);
    shadowTask->init(SHADOW_TASK_PERIOD);

    sched.init(SCHED_PERIOD);
    sched.addTask(shadowTask);
    sched.addTask(windTask);
}

void loop() {
    sched.schedule();
}