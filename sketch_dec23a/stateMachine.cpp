#include "stateMachine.h"
#include "support.h"

void fn_StateINIT(){
    Serial.println("Status INIT \n");
    delay(5000);
    if(dispenserValue < portionSize){
        currentState = EMPTY;
    }else{
        currentState = STAND_BY;
    }
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