#include "stateMachine.h"
#include "servoSupport.h"
#include "scaleSupport.h"
#include "timerSupport.h"
#include "wifiSupport.h"
#include "webServerSupport.h"

//TO BE MOVED
volatile float portionSize = 0.0; //expressed in grams // da spostare forse----------
float dispenserReading = 0.0;
float portionReading = 0.0;

volatile State_t currentState = INIT;

// Synchronization interval (e.g., every 12 hours)

void setup() {
    Serial.begin(115200);
    // Connect to Wi-Fi for synchronization
    initWiFi("HomeLife_Fibra", "grepolis2003");
    //Check if connected to Wi-Fi
    checkWifiStatus();

    startWebServer();

    syncTimeWithNTP();
    lastSyncTime = millis();  // Record the last synchronization time
    esp_sleep_enable_wifi_wakeup();
    initDevices();

}

void loop() {

    Serial.println("\nCurrent local time: " + getCurrentTime() +"\n");
    delay(3000);

    //Serial.println(scale_portion.get_units(), 1);
//    Serial.println(scale_dispenser.get_units(5), 1);

    if(currentState < NUM_STATES){
        (*StateMachine[currentState].state_func)();
    }
    else{
        Serial.println("State machine error!");
    }

    //Serial.println("Motor On");
    //digitalWrite(VIBRATION_PIN, HIGH);
    //delay(300);

    //Serial.println("Motor OFF");
    //digitalWrite(VIBRATION_PIN, LOW);

}