#ifndef switches_included
#define switches_included

#include "movementB.h"
#include <shape.h>

#define SW0 BIT0
#define SW1 BIT1
#define SW2 BIT2
#define SW3 BIT3
#define SWITCHES (SW1 | SW0 | SW2 | SW3)

void switch_init();

//THIS WILL MANIPULATE THE LAYERS AND THE REGION TO KNOW WHERE TO MANIPULATE
void switch_interrupt_handler(MovLayer *ml, Region *fence);

extern short cheatState;
// This will keep track of the state in where the user wants to cheat

#endif //included

