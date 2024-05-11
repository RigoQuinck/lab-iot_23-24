/*
 * HTTPClient lib -- simple HTTP GET
 */
#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* url = "www.example.com";

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
        Serial.println("WiFi Connected: Do http request.");
        HTTPClient http;

        // Your Domain name with URL path or IP address with path
        http.begin(url);

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(String("Content Length: ") + payload.length());
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        // Free resources
        http.end();

        delay(1000);
    } else {
        Serial.println("WiFi Disconnected... Reconnect.");
        connectToWifi(ssid, password);
    }
}