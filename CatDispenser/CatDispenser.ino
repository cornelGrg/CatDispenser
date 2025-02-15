#include "stateMachine.h"
#include "servoSupport.h"
#include "scaleSupport.h"
#include "timerSupport.h"
#include "wifiSupport.h"
#include "webServerSupport.h"


volatile float portionSize = 0.0; //expressed in grams
float dispenserReading = 0.0;
float portionReading = 0.0;

volatile State_t currentState = INIT;


void setup() {
    Serial.begin(115200);
    // Connect to Wi-Fi for synchronization
    initWiFi("HomeLife_Fibra", "grepolis2003");
    //Check if connected to Wi-Fi
    checkWifiStatus();

    startWebServer();

    syncTimeWithNTP();
    lastSyncTime = millis();  //save the last synchronization time
    initDevices();
}

void loop() {

    if(currentState < NUM_STATES){
        (*StateMachine[currentState].state_func)();
    }
    else{
        Serial.println("State machine error!");
    }

}