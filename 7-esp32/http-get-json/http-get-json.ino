/*
 * HTTPClient lib --  Performing an HTTP REST to our service
 *
 * Going through ngrok
 *
 */
#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// TODO: replace <your_server_address> with your server address
const char* serviceURI = "http://<your_server_address>:3000";

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

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        String servicePath = String(serviceURI) + "/";

        Serial.println(servicePath);

        http.begin(servicePath);

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        // Free resources
        http.end();

        delay(2000);

    } else {
        Serial.println("WiFi Disconnected... Reconnect.");
        connectToWifi(ssid, password);
    }
}
