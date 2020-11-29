#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

static char switch_update_interrupt_sense(){
  // UPDATE SWITCH INTERRUPT TO DETECT CHANGES 
  P2IES |= (p2val & SWITCHES); // SWITCH UP = SENSE DOWN
  P2IES &= (p2val | ~SWITCHES); // SWITCH DON = SENSE UP
  return p2val;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler(MovLayer *ml, Region *fence){
  char p2val = switch_update_interrupt_sense();
  char vel;
  if(!(p2val & SW1)){
    vel = 6;
    ml -> velocity.axes[0] = vel;
    mlAdvance(ml, fence); //move the figure
    ml-> velocity.axes[0] = 0;
  }
  if(!(p2val & SW0)){
    vel = 6;
    ml -> velocity.axes[0] = vel;
    mlAdvanceOpp(ml, fence);
    ml -> velocity.axes[0] = 0;
  }
}
