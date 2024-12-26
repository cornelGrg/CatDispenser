#include "support.h"

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

void calibrateScale(HX711 scale){
    float reading = scale.get_units(10);
    Serial.println("Reading: " + String(reading));
    //calibration factor = (reading)/(known weight in g)
    float calibration_factor = (reading)/(230);  //230gr known object weight
    Serial.println("Calibration factor: " + String(calibration_factor));
    //scale.set_scale(0.42);
    scale.set_scale(calibration_factor);
}