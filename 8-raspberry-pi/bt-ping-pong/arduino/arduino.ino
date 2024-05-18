#include <SoftwareSerial.h>

#define TXD 2
#define RXD 3

const char* ping = "PING";
const char* pong = "PONG";

SoftwareSerial btSerial(TXD, RXD);

String message = "";
bool msgAvailable = false;

void btEvent() {
    if (btSerial.available() && !msgAvailable) {
        while (btSerial.available()) {
            char ch = (char)btSerial.read();
            if (ch == '\n') {
                msgAvailable = true;
                Serial.println(message);
            } else {
                message += ch;
            }
        }
    }
}

void setup() {
    Serial.begin(9600);
    btSerial.begin(9600);
}

void loop() {
    btEvent();
    if (msgAvailable) {
        if (message == ping) {
            btSerial.println(pong);
        }
        msgAvailable = false;
        message = "";
    }
}