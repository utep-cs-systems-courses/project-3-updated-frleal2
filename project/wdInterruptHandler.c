#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){
  static char blink_count = 0;
  if (++blink_count == 100){ //made the blink faster 
    state_advance(); //when the led state machine is used to blink back and forth
    blink_count = 0;
  }
}