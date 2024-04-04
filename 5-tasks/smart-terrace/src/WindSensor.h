#ifndef __WIND_SENSOR__
#define __WIND_SENSOR__

class WindSensor {
   public:
    virtual float getWindSpeed() = 0;
};

#endif