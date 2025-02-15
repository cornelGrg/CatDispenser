#include "scaleSupport.h"
HX711 scale_portion;
HX711 scale_dispenser;

void calibrateScale(HX711* scale, float calibration_factor){
    delay(2000);
    scale->set_scale(1.0);  //set scale factor to 1 for raw readings
    scale->tare();

    //Calculation of the calibration factor
//    Serial.println("Put the known weight object");
//    delay(5000);

//    for (int i = 0; i < 10; ++i) {
//        Serial.println(scale->get_units(10));
//    }

//    float reading = scale->get_units(10);
//    Serial.println("Reading: " + String(reading));
//     calibration factor = (reading)/(known weight in g)
//    float calibration_factorTest = (reading)/(213.0);  //243gr known object weight
//    Serial.println("Calibration factor: " + String(calibration_factor));
    //scale->set_scale(0.42);

    scale->set_scale(calibration_factor);
    delay(3000);
    Serial.println("Finished calibration");
}