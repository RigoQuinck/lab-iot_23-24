#ifndef __MYSERVO__
#define __MYSERVO__

class MyServo {
   public:
    virtual void setAngle(int newPos) = 0;
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual int getAngle() = 0;
};
#endif
