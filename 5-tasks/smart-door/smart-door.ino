#include "src/AlertTask.h"
#include "src/DoorTask.h"
#include "src/Led.h"
#include "src/Motor.h"
#include "src/Pir.h"
#include "src/Scheduler.h"
#include "src/TemperatureSensorImpl.h"

#define TEMP_PIN A4
#define LED_PIN 12
#define PIR_PIN 7
#define SERVO_PIN 9

#define DOOR_TASK_PERIOD 500
#define ALERT_TASK_PERIOD 1000
#define SCHED_PERIOD 500

Scheduler sched;

void setup() {
    TemperatureSensor *tempSensor = new TemperatureSensorImpl(TEMP_PIN);
    Light *light = new Led(LED_PIN);
    AlertTask *alertTask = new AlertTask(tempSensor, light);
    alertTask->init(ALERT_TASK_PERIOD);

    Presence *presence = new Pir(PIR_PIN);
    MyServo *myservo = new Motor(SERVO_PIN);
    DoorTask *doorTask = new DoorTask(presence, myservo, alertTask);
    doorTask->init(DOOR_TASK_PERIOD);

    sched.init(SCHED_PERIOD);
    sched.addTask(alertTask);
    sched.addTask(doorTask);
}

void loop() {
    sched.schedule();
}