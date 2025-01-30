#include "stateMachine.h"

StateMachine_t StateMachine[] = {
        {INIT, fn_StateINIT},
        {STAND_BY, fn_StateSTANDBY},
        {DISPENSE, fn_StateDISPENSE},
        {EMPTY, fn_StateEMPTY},
        {REFILL, fn_StateREFILL},
};

void fn_StateINIT(){
    Serial.println("Status INIT \n");
    delay(5000);
//    if(dispenserValue < portionSize){
//        currentState = EMPTY;
//    }else{
//        currentState = STAND_BY;
//    }
    currentState = EMPTY;
}

void fn_StateSTANDBY(){
    //check time
    Serial.println("Status STANDBY \n");
    delay(5000);
    currentState = DISPENSE;
}

void fn_StateDISPENSE(){
    Serial.println("Status DISPENSE \n");
    delay(5000);
    openServo();
    currentState = EMPTY;
}

void fn_StateEMPTY(){
    Serial.println("Status EMPTY \n");
    delay(5000);
    closeServo();
    currentState = STAND_BY;
}

void fn_StateREFILL(){
    Serial.println("Status REFILL \n");
    delay(5000);
    currentState = STAND_BY;
}

void initDevices(){
    //configure servo motor
    servo1.attach(SERVO_PIN);

    //configure vibration motor
    pinMode(VIBRATION_PIN, OUTPUT);


    //configure scale portion
    scale_portion.begin(LOADCELL_PORTION_DOUT_PIN, LOADCELL_PORTION_SCK_PIN);

//    Serial.println("Calibrating portion scale \n");
//    delay(2000);
//    calibrateScale(scale_portion);
//    Serial.println("Portion scale calibrated! \n");

    //configure scale dispenser
    scale_dispenser.begin(LOADCELL_DISPENSER_DOUT_PIN, LOADCELL_DISPENSER_SCK_PIN);  
//    Serial.println("Calibrating dispenser scale \n");
//    delay(2000);
//    calibrateScale(scale_dispenser);
//    Serial.println("Dispenser scale calibrated! \n");

//    scale_portion.tare();
//    scale_dispenser.tare();
}