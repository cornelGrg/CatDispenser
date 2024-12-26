#ifndef CATDISPENSER_SUPPORT_H
#define CATDISPENSER_SUPPORT_H
#include <ESP32Servo.h>
#include <Arduino.h>
#include "HX711.h"

void openServo();
void closeServo();
void calibrateScale();


#endif //CATDISPENSER_SUPPORT_H
