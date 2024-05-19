#include <ArduinoJson.h>

void setup() {
    Serial.begin(9600);
}

String serialize() {
    // Crea un oggetto JSON
    JsonDocument doc;
    doc["type"] = "distance";
    doc["value"] = 1.1;

    // Serializza l'oggetto JSON in una stringa
    String json;
    serializeJson(doc, json);

    Serial.println("Json value serialized: " + json);

    return json;
}

void deserialize(String json) {
    JsonDocument doc;
    deserializeJson(doc, json);

    String type = doc["type"];
    double value = doc["value"];

    Serial.println("Type: " + type);
    Serial.println(String("Value: ") + value);
}

void loop() {
    String json = serialize();
    deserialize(json);
    delay(10000);
}
