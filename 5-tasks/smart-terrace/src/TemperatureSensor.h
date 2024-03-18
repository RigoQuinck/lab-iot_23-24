#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

class TemperatureSensor {
   public:
    virtual float getTemperature() = 0;
};

#endif