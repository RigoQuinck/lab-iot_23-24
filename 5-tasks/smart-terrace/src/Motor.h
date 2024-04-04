#ifndef __MOTOR__
#define __MOTOR__

#include "MyServo.h"
#include "ServoTimer2.h"

class Motor : public MyServo {
   public:
    Motor(int pin);
    void setAngle(int newPos);
    void forward();
    void backward();
    int getAngle();

   private:
    int pin;
    int pos;
    ServoTimer2 servo;
    int mapPos(int pos);
};

#endif
