#include "src/Led.h"
#include "src/MsgService.h"

#define LED_PIN 8
#define SWITCH_OFF_CMD "0"
#define SWITCH_ON_CMD "1"

enum
{
  ON,
  OFF
} state;

Light *light;

void setup()
{
  light = new Led(LED_PIN);
  MsgService.init();
  MsgService.sendMsg("START");
  state = OFF;
}

void loop()
{
  switch (state)
  {
  case ON:
    lightOn();
    break;
  case OFF:
    lightOff();
    break;
  }
};

bool msgMatch(String cmd)
{
  if (MsgService.isMsgAvailable())
  {
    Msg *msg = MsgService.receiveMsg();
    bool isMatch = msg->getContent() == cmd;
    delete msg;
    return isMatch;
  }
  return false;
}

void lightOn()
{
  if (msgMatch(SWITCH_OFF_CMD))
  {
    light->switchOff();
    MsgService.sendMsg("LED OFF");
    state = OFF;
  }
}

void lightOff()
{
  if (msgMatch(SWITCH_ON_CMD))
  {
    light->switchOn();
    MsgService.sendMsg("LED ON");
    state = ON;
  }
}
