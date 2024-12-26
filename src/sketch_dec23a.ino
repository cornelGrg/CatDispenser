#include <ESP32Servo.h>
#include "HX711.h"
#include "support.h"
#include "stateMachine.h"

//Pin definition
#define SERVO_PIN = 22;
#define VIBRATION_PIN 25
#define LOADCELL_PORTION_DOUT_PIN = 15;
#define LOADCELL_PORTION_SCK_PIN = 5;
#define LOADCELL_DISPENSER_DOUT_PIN = 16;
#define LOADCELL_DISPENSER_SCK_PIN = 4;

float portionSize = 20.0; //expressed in grams
float dispenserValue;
State currentState = INIT;


//State machine definition
StateMachine_t StateMachine[] = {
        {INIT, fn_StateINIT()},
        {STAND_BY, fn_StateSTANDBY()},
        {DISPENSE, fn_StateDISPENSE()},
        {EMPTY, fn_StateEMPTY()},
        {REFILL, fn_StateREFILL()},
};

Servo servo1;
HX711 scale_portion;
HX711 scale_dispenser;


void setup() {
    Serial.begin(115200);

    //configure servo motor
//    servo1.attach(SERVO_PIN);

    //configure vibration motor
//    pinMode(VIBRATION_PIN, OUTPUT);

    Serial.println("Initializing the scale \n");

    //configure scale portion
//    scale_portion.begin(LOADCELL_PORTION_DOUT_PIN, LOADCELL_PORTION_SCK_PIN);

//    Serial.println("Calibrating portion scale \n");
//    delay(2000);
//    calibrateScale(scale_portion);
//    Serial.println("Portion scale calibrated! \n");

    //configure scale portion
//    scale_dispenser.begin(LOADCELL_DISPENSER_DOUT_PIN, LOADCELL_DISPENSER_SCK_PIN);

//    Serial.println("Calibrating dispenser scale \n");
//    delay(2000);
//    calibrateScale(scale_dispenser);
//    Serial.println("Dispenser scale calibrated! \n");

//    scale_portion.tare();
//    scale_dispenser.tare();


}

void loop() {
//    dispenserValue = scale_dispenser.get_units(10);  //updates dispenser/1s
    dispenserValue = 100.0;
//    delay(1000);
    //openServo();
    //delay(1000);

    //closeServo();
    //delay(1000);

    //Serial.println(scale_portion.get_units(), 1);
//    Serial.println(scale_dispenser.get_units(5), 1);
    if(current_state < NUM_STATES){
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