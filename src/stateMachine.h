#ifndef CATDISPENSER_STATEMACHINE_H
#define CATDISPENSER_STATEMACHINE_H
#include <Arduino.h>

//State definition
typedef enum State_t {
    INIT,
    STAND_BY,
    DISPENSE,
    EMPTY,
    REFILL
} State_t;

typedef_struct{
    State_t state;
    void (*state_func)(void);
} StateMachine_t;

void fn_StateINIT();
void fn_StateSTANDBY();
void fn_StateDISPENSE();
void fn_StateEMPTY();
void fn_StateREFILL();


#endif //CATDISPENSER_STATEMACHINE_H
