<<<<<<< HEAD
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

=======
#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
       /* switch1 is p1.3 */
#define SWITCHES SW1 | SW2 | SW3 | SW4    /* only 1 switch on this board */

void switch_init();
char switch_interrupt_handler();

extern char sw1_state_down, sw2_state_down, sw3_state_down, sw4_state_down; /* effectively boolean */

#endif // included
>>>>>>> 7f5ad9a2c08b4f16179862b2cc693b75dda0b693
