#include <avr/sleep.h>

#define BTN_PIN 2

void wakeUp() {}

void setup()
{
    Serial.begin(9600);
    Serial.flush();
    pinMode(BTN_PIN, INPUT);
}

void goToSleep()
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(digitalPinToInterrupt(BTN_PIN), wakeUp, RISING);
    sleep_mode();
}

void disableSleep()
{
    sleep_disable();
    detachInterrupt(digitalPinToInterrupt(BTN_PIN));
}

void loop()
{
    Serial.println("Going to sleep in 1s ...");
    Serial.flush();
    delay(1000);

    goToSleep();

    disableSleep();

    // Do after wake up
    Serial.println("WAKE UP");
}