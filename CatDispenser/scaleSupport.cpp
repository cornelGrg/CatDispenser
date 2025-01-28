#include "scaleSupport.h"
HX711 scale_portion;
HX711 scale_dispenser;

void calibrateScale(HX711 scale){
    float reading = scale.get_units(10);
    Serial.println("Reading: " + String(reading));
    //calibration factor = (reading)/(known weight in g)
    float calibration_factor = (reading)/(230);  //230gr known object weight
    Serial.println("Calibration factor: " + String(calibration_factor));
    //scale.set_scale(0.42);
    scale.set_scale(calibration_factor);
}