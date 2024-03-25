#include <Servo.h>

#include "LightSensor.h"
#include "Task.h"
#include "TemperatureSensor.h"

class ShadowTask : public Task {
   public:
    ShadowTask(int tempPin, int lightSensorPin, int servoPin);
    void init(int period);
    void tick();

   private:
    int tempPin;
    int lightSensorPin;
    int servoPin;
    LightSensor *lightSensor;
    TemperatureSensor *temp;
    Servo servo;
    enum { DOWN, UP, MOVING } state;
    int direction;

    void up();
    void down();
    void moving();
};