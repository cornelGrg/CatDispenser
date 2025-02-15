#ifndef CATDISPENSER_STATEMACHINE_H
#define CATDISPENSER_STATEMACHINE_H
#include <Arduino.h>
#include <esp_wifi.h>
#include <vector>
#include <algorithm>
#include <ESPAsyncWebServer.h>
#include "servoSupport.h"
#include "scaleSupport.h"
#include "timerSupport.h"
#include "powerSaving.h"

#define SERVO_INT_PIN 22
#define SERVO_EXT_PIN 23
#define VIBRATION_PIN 21
#define LOADCELL_PORTION_DOUT_PIN 15
#define LOADCELL_PORTION_SCK_PIN 5
#define LOADCELL_DISPENSER_DOUT_PIN 19
#define LOADCELL_DISPENSER_SCK_PIN 18

//State definition
typedef enum State_t {
    INIT,
    STAND_BY,
    DISPENSE,
    REFILL,
    NUM_STATES
} State_t;

typedef struct{
    State_t state;
    void (*state_func)(void);
} StateMachine_t;

static String lastReturnedSlot;

extern volatile float portionSize; //expressed in grams
extern std::vector<String> dispenseTimes; //array with time slots
extern float dispenserReading;
extern float portionReading;
volatile extern State_t currentState;
extern AsyncEventSource events;

void fn_StateINIT();
void fn_StateSTANDBY();
void fn_StateDISPENSE();
void fn_StateREFILL();
void initDevices();
void dispense();
extern void sendNotification(String message);
String getNextTimeSlot();

//State machine definition
extern StateMachine_t StateMachine[];

#endif //CATDISPENSER_STATEMACHINE_H
