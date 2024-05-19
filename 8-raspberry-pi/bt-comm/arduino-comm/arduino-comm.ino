#include "src/BluetoothEventCatcher.h"
#include "src/BluetoothMsgService.h"
#include "src/LoggerTask.h"
#include "src/ProducerTask.h"
#include "src/Scheduler.h"
#include "src/SerialMsgService.h"

#define SER_MSG_SERVICE_NAME "OUT"
#define SER_MSG_SERVICE_BAUD_RATE 9600
#define BT_MSG_SERVICE_NAME "BT"
#define BT_MSG_SERVICE_BAUD_RATE 9600
#define BT_TXD_PIN 2
#define BT_RXD_PIN 3
#define BT_STATE_PIN 4
#define BT_EVENT_CATCHER_TASK_PERIOD 100
#define LOGGER_TASK_PERIOD 100
#define PRODUCER_TASK_PERIOD 100
#define SCHED_PERIOD 100

Scheduler sched;

void setup() {
    SerialMsgService* serial = new SerialMsgService(SER_MSG_SERVICE_NAME, SER_MSG_SERVICE_BAUD_RATE);
    BluetoothMsgService* bt =
        new BluetoothMsgService(BT_MSG_SERVICE_NAME, BT_TXD_PIN, BT_RXD_PIN, BT_STATE_PIN, BT_MSG_SERVICE_BAUD_RATE);

    BluetoothEventCatcher* btEventCatcher = new BluetoothEventCatcher(bt);
    btEventCatcher->init(BT_EVENT_CATCHER_TASK_PERIOD);

    LoggerTask* loggerTask = new LoggerTask(bt, serial);
    loggerTask->init(LOGGER_TASK_PERIOD);

    ProducerTask* producerTask = new ProducerTask(bt);
    producerTask->init(PRODUCER_TASK_PERIOD);

    sched.init(SCHED_PERIOD);
    sched.addTask(btEventCatcher);
    sched.addTask(loggerTask);
    sched.addTask(producerTask);
}

void loop() {
    sched.schedule();
}
