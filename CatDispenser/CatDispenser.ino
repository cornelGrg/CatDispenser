#include "scaleSupport.h"
#include "servoSupport.h"
#include "stateMachine.h"
#include "timerSupport.h"
#include "wifiSupport.h"
#include "webServerSupport.h"

float portionSize = 25.0; //expressed in grams // da spostare forse----------
float dispenserReading = 0.0;
float portionReading = 0.0;
State_t currentState = INIT;

// Synchronization interval (e.g., every 12 hours)
unsigned int lastSyncTime = 0;

void setup() {
    Serial.begin(115200);
    // Connect to Wi-Fi for synchronization
    initWiFi("HomeLife_Fibra", "grepolis2003");
    //Check if connected to Wi-Fi
    checkWifiStatus();

    startWebServer();

    syncTimeWithNTP();
    lastSyncTime = millis();  // Record the last synchronization time

    initDevices();
}

void loop() {

    for (int i = 0; i < 10; ++i) {
        dispenserReading = i*100 ;
        portionReading =  i*100;
        delay(2000);
    }


    if (isSyncDue(lastSyncTime)) {
        syncTimeWithNTP();
        lastSyncTime = millis();
    }

    Serial.println(getCurrentTime());
//    dispenserValue = scale_dispenser.get_units(10);  //updates dispenser/1s

    //Serial.println(scale_portion.get_units(), 1);
//    Serial.println(scale_dispenser.get_units(5), 1);

    if(currentState < NUM_STATES){
        (*StateMachine[currentState].state_func)();
    }
    else{
        Serial.println("ERROR!");
    }

    //Serial.println("Motor On");
    //digitalWrite(VIBRATION_PIN, HIGH);
    //delay(300);

    //Serial.println("Motor OFF");
    //digitalWrite(VIBRATION_PIN, LOW);

}