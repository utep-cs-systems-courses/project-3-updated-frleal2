<<<<<<< HEAD
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
=======
#include <msp430.h>
#include "switches.h"
//#include "led.h"
//#include "buzzer.h"
#include "stateMachines.h"

char sw1_state_down,sw2_state_down,sw3_state_down,sw4_state_down;
int switch_state = 0;
//char switch_state_down, switch_state_changed; // effectively boolean


static char switch_update_interrupt_sense() {
  char p2val = P2IN;
  // update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES);    // if switch up, sense down
  P2IES &= (p2val | ~SWITCHES);   // if switch down, sense up
  return p2val;
}

void
switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

char switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();

  sw1_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  sw2_state_down = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  sw3_state_down = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  sw4_state_down = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */

  if(sw1_state_down){
    switch_state = 1;
    state_advance();
  }

  if(sw2_state_down){
    switch_state = 2;
    state_advance();
  }

  if(sw3_state_down){
    switch_state = 3;
    state_advance();
  }

  if(sw4_state_down){
    switch_state = 4;
    state_advance();
  }
  
}
>>>>>>> 7f5ad9a2c08b4f16179862b2cc693b75dda0b693
