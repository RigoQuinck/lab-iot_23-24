#include <SoftwareSerial.h>

#define TXD 2
#define RXD 3

SoftwareSerial btSerial(TXD, RXD);

void setup() {
    Serial.begin(9600);
    btSerial.begin(38400);
}

void loop() {
    if (btSerial.available()) {
        Serial.write(btSerial.read());
    }
    if (Serial.available()) {
        btSerial.write(Serial.read());
    }
}