#include <ESP32Servo.h>
#include "HX711.h"

static const int servoPin = 22;
#define vibratorPin 25
/**static const int LOADCELL1_DOUT_PIN = 15;
static const int LOADCELL1_SCK_PIN = 4;
**/
static const int LOADCELL2_DOUT_PIN = 16;
static const int LOADCELL2_SCK_PIN = 4;


Servo servo1;
//HX711 scale1;
HX711 scale2;

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


void setup() {
  Serial.begin(115200);
  servo1.attach(servoPin);

  // Set MOTOR_PIN as an output
  pinMode(vibratorPin, OUTPUT);

  Serial.println("Initializing the scale \n");
  //scale1.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  scale2.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);

  float reading = scale2.get_units(10);
  Serial.println("Reading: " + String(reading));
  //calibration factor = (reading)/(known weight in g)
  float calibration_factor = (-157300)/(230);
  //Serial.println("Calibration factor: " + String(calibration_factor));
  //scale1.set_scale(0.42);
  scale2.set_scale(calibration_factor);           // this value is obtained by calibrating the scale with known weights; see the README for details
  //scale1.tare();   
  scale2.tare();    // reset the scale to 0

}

void loop() {
  //openServo();
  //delay(1000);

  //closeServo();
  //delay(1000);

  //Serial.println(scale1.get_units(), 1); 
  Serial.println(scale2.get_units(5), 1); 

  //Serial.println("Motor On");
  //digitalWrite(vibratorPin, HIGH);
  //delay(300);

  //Serial.println("Motor OFF");
  //digitalWrite(vibratorPin, LOW);

}