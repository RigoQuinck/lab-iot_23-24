#include "LightSensor.h"

class LightSensorImpl : public LightSensor {
   public:
    LightSensorImpl(int pin);
    int getLightIntensity();

   private:
    int pin;
    double analogValueToLux(int value);
};
