#include "TemperatureSensor.h"

class TemperatureSensorImpl : public TemperatureSensor {
   private:
    int pin;

   public:
    TemperatureSensorImpl(int pin);
    float getTemperature();
};