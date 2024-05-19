#ifndef __MSG_SERVICE__
#define __MSG_SERVICE__

#include "Arduino.h"
#define MSG_BUFFER_SIZE 5

class MsgService {
   private:
    String queue[MSG_BUFFER_SIZE];
    int head;
    int tail;
    String name;
    void saveMsg(String msg);
    void resetBuffer();

   protected:
    MsgService(String name);
    virtual bool isChannelAvailable() = 0;
    virtual char read() = 0;

   public:
    /**
     * Send an int messagge into the channel.
     */
    virtual void sendMsg(int msg) = 0;
    /**
     * Send a String messagge into the channel.
     */
    virtual void sendMsg(String msg) = 0;
    /**
     * Send a float messagge into the channel.
     */
    virtual void sendMsg(float msg) = 0;
    /**
     * Verify if someone is connected to the channel.
     * @return true if someone is connected to the channel
     */
    virtual bool isConnected() = 0;
    /**
     * Get the name of the channel.
     * @return the name of the channel
     */
    String getName();
    /**
     * Get oldest received message.
     * @return the oldest received message otherwise NULL.
     */
    String receiveMsg();
    /**
     * Check if there is an available message.
     * @return true if there is an available message otherwise false
     */
    bool isMsgAvailable();
    /**
     * Check if there are new data from the channel, in the afferamative case collects the new data and create a new
     * message.
     */
    void channelEvent();
};

#endif
