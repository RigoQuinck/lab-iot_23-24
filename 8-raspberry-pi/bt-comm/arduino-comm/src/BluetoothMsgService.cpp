#include "BluetoothMsgService.h"

#include "Arduino.h"

BluetoothMsgService::BluetoothMsgService(String name, uint8_t pinTDX, uint8_t pinRDX, uint8_t pinState,
                                         unsigned long baudRate)
    : MsgService(name) {
    this->channel = new SoftwareSerial(pinTDX, pinRDX);
    this->channel->begin(baudRate);
    pinMode(pinState, INPUT);
    this->pinState = pinState;
}

bool BluetoothMsgService::isConnected() {
    return digitalRead(this->pinState);
}

void BluetoothMsgService::sendMsg(String msg) {
    this->channel->println(msg);
    this->channel->flush();
}

void BluetoothMsgService::sendMsg(int msg) {
    this->sendMsg(String(msg));
}

void BluetoothMsgService::sendMsg(float msg) {
    this->sendMsg(String(msg));
}

bool BluetoothMsgService::isChannelAvailable() {
    return this->channel->available();
}

char BluetoothMsgService::read() {
    return (char)this->channel->read();
}
