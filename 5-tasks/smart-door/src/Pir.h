#ifndef __PIR__
#define __PIR__

#include "Presence.h"

class Pir : public Presence {
   public:
    Pir(int pin);
    bool isPresent();

   private:
    int pin;
};

#endif