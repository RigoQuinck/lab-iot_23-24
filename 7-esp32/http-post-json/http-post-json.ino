#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// TODO: replace <your_server_address> with your server address
const char* serviceURI = "http://192.168.1.20:3000";

void connectToWifi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    connectToWifi(ssid, password);
}

String ping(String address, String message) {
    HTTPClient http;
    http.begin(address + "/ping");
    http.addHeader("Content-Type", "application/json");

    String msg = "{ \"message\": \"" + message + "\" }";

    int retCode = http.POST(msg);

    String reply = "";
    if (retCode == 200) {
        reply = http.getString();
    }

    http.end();

    return reply;
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        int value = random(15, 20);
        unsigned long ts = millis();
        String message = String("Message from ESP32 at ") + ts;
        Serial.println("Ping message: " + message);
        String reply = ping(serviceURI, message);
        if (reply != "") {
            Serial.println(reply);
        } else {
            Serial.println("error");
        }

        delay(2000);

    } else {
        Serial.println("WiFi Disconnected... Reconnect.");
        connectToWifi(ssid, password);
    }
}
