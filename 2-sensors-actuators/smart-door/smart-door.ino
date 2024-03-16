#define PIR_PIN 8
#define SERVO_PIN 3

#define DOOR_COLSED_ANGLE 0
#define DOOR_OPENED_ANGLE 90
#define DOOR_OPEN_MS 10000

#include <Servo.h>

bool detectedStatus;
Servo doorMotor;

void setup()
{
    pinMode(PIR_PIN, INPUT);
    doorMotor.attach(SERVO_PIN);
    doorMotor.write(DOOR_COLSED_ANGLE);

    Serial.begin(9600);
    Serial.flush();

    // give the sensor some time to calibrate
    Serial.print("Calibrating sensor... ");
    delay(2000);
    Serial.println(" done");
    Serial.println("PIR SENSOR READY.");

    detectedStatus = false;
}

void loop()
{
    int current = digitalRead(PIR_PIN);
    if (current)
    {
        Serial.println("Door will open for 10 seconds.");

        Serial.println("Door opening...");
        doorMotor.write(DOOR_OPENED_ANGLE);
        Serial.println("Door opened");

        delay(DOOR_OPEN_MS);

        Serial.println("Door closing...");
        doorMotor.write(DOOR_COLSED_ANGLE);
        Serial.println("Door closed");
    }
};
