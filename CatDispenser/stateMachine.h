#ifndef CATDISPENSER_STATEMACHINE_H
#define CATDISPENSER_STATEMACHINE_H
#include <Arduino.h>
#include <servoSupport.h>

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
extern float dispenserValue;
extern State_t currentState;

void fn_StateINIT();
void fn_StateSTANDBY();
void fn_StateDISPENSE();
void fn_StateEMPTY();
void fn_StateREFILL();

//State machine definition
extern StateMachine_t StateMachine[];


#endif //CATDISPENSER_STATEMACHINE_H
