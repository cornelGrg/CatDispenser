#include "servoSupport.h"
Servo servo1;

void openServo(){
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        delay(10);

    }
    Serial.println("Servo opened \n");
}

void closeServo(){
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(10);
    }
    Serial.println("Servo closed \n");
}