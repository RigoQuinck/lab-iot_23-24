#include "LoggerTask.h"

LoggerTask::LoggerTask(MsgService* inputChannel, MsgService* outputChannel) {
    this->inputChannel = inputChannel;
    this->outputChannel = outputChannel;
}

void LoggerTask::tick() {
    if (this->inputChannel->isMsgAvailable()) {
        String msg = this->inputChannel->receiveMsg();
        if (msg != NULL) {
            this->outputChannel->sendMsg(msg);
        }
    }
}