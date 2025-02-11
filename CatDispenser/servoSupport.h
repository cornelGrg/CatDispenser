#ifndef CATDISPENSER_SERVO_H
#define CATDISPENSER_SERVO_H
#include <ESP32Servo.h>

extern Servo servoInternal;
extern Servo servoExternal;

void openServo(Servo* servo, int angle, int del);
void closeServo(Servo* servo, int angle, int del);

#endif
