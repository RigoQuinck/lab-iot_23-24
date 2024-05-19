#ifndef __PRODUCER_TASK__
#define __PRODUCER_TASK__

#include "MsgService.h"
#include "Task.h"

class ProducerTask : public Task {
   private:
    MsgService* msgService;

   public:
    ProducerTask(MsgService* msgService);
    void tick();
};

#endif
