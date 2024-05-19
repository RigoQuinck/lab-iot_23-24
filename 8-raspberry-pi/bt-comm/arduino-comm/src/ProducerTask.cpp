#include "ProducerTask.h"

ProducerTask::ProducerTask(MsgService* msgService) {
    this->msgService = msgService;
}

void ProducerTask::tick() {
    if (msgService->isConnected()) {
        unsigned long data = millis();
        this->msgService->sendMsg(String("Arduino timestamp: ") + data);
    }
}