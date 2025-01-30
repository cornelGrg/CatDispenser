#ifndef CATDISPENSER_STATEMACHINE_H
#define CATDISPENSER_STATEMACHINE_H
#include <Arduino.h>
#include "servoSupport.h"
#include "scaleSupport.h"

#define SERVO_PIN 22
#define VIBRATION_PIN 25
#define LOADCELL_PORTION_DOUT_PIN 15
#define LOADCELL_PORTION_SCK_PIN 5
#define LOADCELL_DISPENSER_DOUT_PIN 16
#define LOADCELL_DISPENSER_SCK_PIN 4

//State definition
typedef enum State_t {
    INIT,
    STAND_BY,
    DISPENSE,
    EMPTY,
    REFILL,
    NUM_STATES
} State_t;

typedef struct{
    State_t state;
    void (*state_func)(void);
} StateMachine_t;

extern float portionSize; //expressed in grams
extern std::vector<String> dispenseTimes; //array with time slots
extern float dispenserReading;
extern float portionReading;
extern State_t currentState;

void fn_StateINIT();
void fn_StateSTANDBY();
void fn_StateDISPENSE();
void fn_StateEMPTY();
void fn_StateREFILL();
void initDevices();

//State machine definition
extern StateMachine_t StateMachine[];

#endif //CATDISPENSER_STATEMACHINE_H
