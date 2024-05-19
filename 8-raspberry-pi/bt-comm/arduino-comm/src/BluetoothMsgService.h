#ifndef __BLUETOOTH_MSG_SERVICE__
#define __BLUETOOTH_MSG_SERVICE__

#include "Arduino.h"
#include "MsgService.h"
#include "SoftwareSerial.h"

/**
 * MsgService that use the BluetoothTechnology.
 */
class BluetoothMsgService : public MsgService {
   private:
    SoftwareSerial* channel;
    uint8_t pinState;

   protected:
    char read();

   public:
    void sendMsg(String msg);
    void sendMsg(float msg);
    void sendMsg(int msg);
    BluetoothMsgService(String name, uint8_t pinTDX, uint8_t pinRDX, uint8_t pinState, unsigned long baudRate);
    bool isChannelAvailable();
    bool isConnected();
};

#endif
