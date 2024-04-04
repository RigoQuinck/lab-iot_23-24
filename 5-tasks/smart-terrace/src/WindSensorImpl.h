#ifndef __WIND_SENSOR_IMPL__
#define __WIND_SENSOR_IMPL__

#include "WindSensor.h"

class WindSensorImpl : public WindSensor {
   public:
    WindSensorImpl(int pin);
    float getWindSpeed();

   private:
    int pin;
};

#endif