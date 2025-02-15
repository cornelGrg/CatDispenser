#include "servoSupport.h"
Servo servoInternal;
Servo servoExternal;

void openServo(Servo* servo, int angle, int del){
    for(int posDegrees = 0; posDegrees <= angle; posDegrees++) {
        servo->write(posDegrees);
        delay(del);

    }
}