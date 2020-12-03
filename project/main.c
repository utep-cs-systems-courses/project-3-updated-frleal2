#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

#define LED_GREEN BIT6  //P1.6

short redrawScreen = 1;

void wdt_c_handler(){
  static int count = 0;

  if(++count == 62 && switch_state == 1){ 
    redrawScreen = 1;
    count = 0;
  }
  else if(count == 250 && switch_state == 2){
    redrawScreen = 1;
    count = 0;
  }
}

int main(){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  
  //state_init();
  configureClocks();
  lcd_init();
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();

  or_sr(0x8);
  
  clearScreen(COLOR_WHITE);
  //drawString5x7(0,0,"TESTING, TESTING", COLOR_WHITE, COLOR_BLACK);

  while(1){ //THIS WILL RUN INFINITELY
    if(redrawScreen){
      redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN; //GREEN IS OFF 
    or_sr(0x18);     //CPU IS OFF
    P1OUT |= LED_GREEN; // GREEN IS ON
  }
}
 

