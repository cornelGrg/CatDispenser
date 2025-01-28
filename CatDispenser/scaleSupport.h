#ifndef CATDISPENSER_SCALE_H
#define CATDISPENSER_SCALE_H
#include "HX711.h"

extern HX711 scale_portion;
extern HX711 scale_dispenser;

void calibrateScale();


#endif //CATDISPENSER_SCALE_H
