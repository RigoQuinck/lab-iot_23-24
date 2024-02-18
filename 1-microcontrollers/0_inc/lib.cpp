#include "lib.h"
#include <arduino.h>

/* public */
int publicFlag;

/* private */
static int incValue = 1;

int increment(int x) {
  delay(1000);
  return x + incValue;
}
