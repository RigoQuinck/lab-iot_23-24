#ifndef __PRINTTASK__
#define __PRINTTASK__

#include "Task.h"

class PrintTask : public Task
{

  int count;

public:
  void init(int period);
  void tick();
};

#endif
