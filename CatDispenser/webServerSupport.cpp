#include "webServerSupport.h"
extern float portionReading;
extern float dispenserReading;
extern float portionSize;

std::vector<String> dispenseTimes;

AsyncWebServer server(80);

void startWebServer(){
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/WebServer.html", String(), false);
    });

    server.on("/sensor-data", HTTP_GET, [](AsyncWebServerRequest *request){
        String json = "{\"dispenser\":" + String(dispenserReading) + ",\"portion\":" + String(portionReading) + "}";
        request->send(200, "application/json", json);
    });

    server.on("/dispense", HTTP_POST, [](AsyncWebServerRequest *request){
        // Simulate dispensing
        Serial.println("Dispensing...");
        request->send(200, "text/plain", "Dispensing completed!");
    });

    server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        if (request->url() == "/save-settings" && request->method() == HTTP_POST) {
            String body = String((char*)data).substring(0, len);
            Serial.println("Received body: " + body);

            // Parse JSON
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, body);

            if (error) {
                Serial.print("JSON parsing failed: ");
                Serial.println(error.c_str());
                request->send(400, "text/plain", "Bad Request: Invalid JSON");
                return;
            }

            // Extract dispense time string and split into time slots
            String dispenseTime = doc["dispenseTime"];
            dispenseTimes = splitString(dispenseTime, '_');
            portionSize = doc["portionSize"];

            Serial.println("Saved time slots:");
            for (const auto &time : dispenseTimes) {
                Serial.println(time);
            }

            Serial.println(portionSize);

            request->send(200, "text/plain", "Time slots saved!");
        }
    });

    server.begin();
    Serial.println("Server enabled!");

}

std::vector<String> splitString(const String &str, char delimiter) {
    std::vector<String> result;
    char buf[str.length() + 1];  // Create a modifiable char array
    str.toCharArray(buf, sizeof(buf));  // Convert String to char array

    char *token = strtok(buf, &delimiter);  // Get first token
    while (token != nullptr) {
        result.push_back(String(token));  // Convert token back to String and store
        token = strtok(nullptr, &delimiter);  // Get next token
    }

    return result;
}