#ifndef __BLUETOOTH_EVENT_CATCHER_TASK__
#define __BLUETOOTH_EVENT_CATCHER_TASK__

#include "BluetoothMsgService.h"
#include "Task.h"

/**
 * Task to catch Bluetooth events of a BluetoothMsgService.
 */
class BluetoothEventCatcher : public Task {
   private:
    BluetoothMsgService* bluetoothMsgService;

   public:
    BluetoothEventCatcher(BluetoothMsgService* bluetoothMsgService);
    void tick();
};

#endif
