#include "MsgService.h"

#include "Arduino.h"

MsgService::MsgService(String name) {
    this->name = name;
    this->resetBuffer();
}

String MsgService::getName() {
    return this->name;
}

String MsgService::receiveMsg() {
    if (this->head != -1) {
        String msg = this->queue[this->head];
        this->head = (this->head + 1) % MSG_BUFFER_SIZE;
        if (this->head > this->tail) {
            this->resetBuffer();
        }
        return msg;
    } else {
        return "";
    }
}

bool MsgService::isMsgAvailable() {
    return this->head != -1;
}

void MsgService::resetBuffer() {
    this->head = -1;
    this->tail = -1;
}

void MsgService::saveMsg(String msg) {
    this->tail = (this->tail + 1) % MSG_BUFFER_SIZE;
    this->queue[this->tail] = msg;
    if (this->tail == this->head || this->head == -1) {
        this->head = (this->head + 1) % MSG_BUFFER_SIZE;
    }
}

void MsgService::channelEvent() {
    if (this->isChannelAvailable()) {
        String content = "";
        while (this->isChannelAvailable()) {
            char ch = this->read();
            Serial.println("[" + this->getName() + "] received: " + String(ch));
            Serial.flush();
            if (ch == '\n') {
                Serial.println("[" + this->getName() + "] received end line with content: " + content);
                Serial.flush();
                this->saveMsg(content);
                content = "";
            } else {
                content += ch;
            }
        }
        Serial.println("[" + this->getName() + "] received: " + content);
        Serial.flush();
    }
}
