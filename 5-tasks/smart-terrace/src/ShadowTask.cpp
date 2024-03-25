#include "ShadowTask.h"

#include "LightSensorImpl.h"
#include "TemperatureSensorImpl.h"

#define SERVO_UP 0
#define SERVO_DOWN 180
#define SERVO_STEP 5
#define UP_DIRECTION -1
#define DOWN_DIRECTION 1

ShadowTask::ShadowTask(int tempPin, int lightSensorPin, int servoPin) {
    this->lightSensorPin = lightSensorPin;
    this->tempPin = tempPin;
    this->servoPin = servoPin;
    state = UP;
}

void ShadowTask::init(int period) {
    lightSensor = new LightSensorImpl(lightSensorPin);
    temp = new TemperatureSensorImpl(tempPin);
    servo.attach(servoPin);
    servo.write(SERVO_UP);
    state = UP;
}

// Quando la luminosità raggiunge 10000 e la temperatura esterna è più alta di 28 gradi, abbasso il tendone.
// Quando la limunosità cala raggiunge 400 alzo il tendone.
void ShadowTask::tick() {
    // Serial.println("TICK");
    switch (state) {
        case UP:
            up();
            break;
        case DOWN:
            down();
            break;
        case MOVING:
            moving();
            break;
    }
}

void ShadowTask::up() {
    int lux = this->lightSensor->getLightIntensity();
    double temp = this->temp->getTemperature();
    // Serial.println(String("LUX ") + lux);
    // Serial.println(String("TEMP ") + temp);
    if (lux >= 10000 && temp >= 28) {
        Serial.println("going down");
        // servo.write(SERVO_DOWN);
        direction = DOWN_DIRECTION;
        state = MOVING;
    }
}

void ShadowTask::down() {
    int lux = this->lightSensor->getLightIntensity();
    if (lux <= 400) {
        Serial.println("going up");
        // servo.write(SERVO_UP);
        // state = UP;
        direction = UP_DIRECTION;
        state = MOVING;
    }
}

void ShadowTask::moving() {
    int curr = servo.read();
    int newPos = curr + SERVO_STEP * direction;
    Serial.println(String("CURR POS ") + curr);
    Serial.println(String("NEW POS ") + newPos);
    servo.write(newPos);
    if (newPos == SERVO_DOWN) {
        state = DOWN;
    }
    if (newPos == SERVO_UP) {
        state = UP;
    }
}