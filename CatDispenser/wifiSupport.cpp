#include "wifiSupport.h"

void initWiFi(const char* ssid, const char* password) {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        Serial.print("Connecting to Wi-Fi");
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }
        Serial.println("\nConnected to Wi-Fi");
    }
}

void disconnectWiFi() {
    WiFi.disconnect(true);  // Disconnect Wi-Fi
    WiFi.mode(WIFI_OFF);    // Turn off Wi-Fi to save power
    Serial.println("Wi-Fi disconnected and turned off");
}

void checkWifiStatus(){
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
