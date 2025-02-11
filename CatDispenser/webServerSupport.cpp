#include "webServerSupport.h"
std::vector<String> dispenseTimes;


AsyncWebServer server(80);
AsyncEventSource events("/events");

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
        currentState = DISPENSE;
        Serial.println("Dispensing...");
        request->send(200, "text/plain", "Dispensing completed!");
    });

    server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        if (request->url() == "/save-settings" && request->method() == HTTP_POST) {
            currentState = INIT;

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
            savedTimes = dispenseTime;

            dispenseTimes = splitString(dispenseTime, '_');
            portionSize = doc["portionSize"];

            request->send(200, "text/plain", "Time slots saved!");
        }
    });

    // Handler per caricare gli slot salvati
    server.on("/get-settings", HTTP_GET, [](AsyncWebServerRequest *request) {
        //Serial.println("Calling loadSlotsFromServer() function");
        Serial.println(savedTimes);

        // Creiamo il JSON con gli slot salvati
        StaticJsonDocument<200> doc;
        doc["slots"] = savedTimes;
        doc["portion"] = portionSize;
        doc["currentState"] = currentState == REFILL ? "REFILL" : "STAND_BY";  // Send current state

        // Serializziamo il JSON
        String jsonResponse;
        serializeJson(doc, jsonResponse);

        // Inviamo la risposta
        request->send(200, "application/json", jsonResponse);
    });

    server.addHandler(&events);
    server.begin();
    Serial.println("Server enabled!");

}

void sendNotification(String message){  //used to send notifications using the CallMeBotAPI
    Serial.println("Notification to telegram sent!");
    // Data to send with HTTP POST
    String url = "https://api.callmebot.com/telegram/group.php?apikey=LTQ2NTkxNjU0NDI&text=" + urlEncode(message);
    HTTPClient http;
    http.begin(url);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Send HTTP POST request
    int httpResponseCode = http.POST(url);
    if (httpResponseCode == 200){
        Serial.println("Message sent successfully");
    }
    else{
        Serial.println("Error sending the message");
        Serial.println("HTTP response code: ");
        Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
}

std::vector<String> splitString(const String &str, char delimiter) {
    std::vector<String> result;
    int start = 0;
    int end = str.indexOf(delimiter);

    while (end != -1) {
        result.push_back(str.substring(start, end));
        start = end + 1;
        end = str.indexOf(delimiter, start);
    }

    result.push_back(str.substring(start));  // Add the last part
    return result;
}