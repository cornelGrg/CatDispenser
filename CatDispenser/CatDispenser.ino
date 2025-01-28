#include "scaleSupport.h"
#include "servoSupport.h"
#include "stateMachine.h"
#include "timerSupport.h"
#include "wifiSupport.h"
#include "webServerSupport.h"

//Pin definition
#define SERVO_PIN 22
#define VIBRATION_PIN 25
#define LOADCELL_PORTION_DOUT_PIN 15
#define LOADCELL_PORTION_SCK_PIN 5
#define LOADCELL_DISPENSER_DOUT_PIN 16
#define LOADCELL_DISPENSER_SCK_PIN 4

float portionSize = 25.0; //expressed in grams // da spostare forse----------
float dispenserValue; // da spostare forse------------------------------------
State_t currentState = INIT;

// Synchronization interval (e.g., every 12 hours)
unsigned int lastSyncTime = 0;

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi for synchronization
    initWiFi("HomeLife_Fibra", "grepolis2003");
    //Check if connected to Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    syncTimeWithNTP();
    lastSyncTime = millis();  // Record the last synchronization time


    //configure servo motor
    servo1.attach(SERVO_PIN);
    //configure vibration motor
//    pinMode(VIBRATION_PIN, OUTPUT);

    Serial.println("Initializing the scale \n");

    //configure scale portion
//    scale_portion.begin(LOADCELL_PORTION_DOUT_PIN, LOADCELL_PORTION_SCK_PIN);

//    Serial.println("Calibrating portion scale \n");
//    delay(2000);
//    calibrateScale(scale_portion);
//    Serial.println("Portion scale calibrated! \n");

//    configure scale portion
//    scale_dispenser.begin(LOADCELL_DISPENSER_DOUT_PIN, LOADCELL_DISPENSER_SCK_PIN);

//    Serial.println("Calibrating dispenser scale \n");
//    delay(2000);
//    calibrateScale(scale_dispenser);
//    Serial.println("Dispenser scale calibrated! \n");

//    scale_portion.tare();
//    scale_dispenser.tare();

}

void loop() {
    startWebServer();

    if (isSyncDue(lastSyncTime)) {
        syncTimeWithNTP();
        lastSyncTime = millis();
    }

    Serial.println(getCurrentTime());
//    dispenserValue = scale_dispenser.get_units(10);  //updates dispenser/1s
    dispenserValue = 100.0;
//    delay(1000);
//    openServo();
//    delay(1000);

    //closeServo();
    //delay(1000);

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