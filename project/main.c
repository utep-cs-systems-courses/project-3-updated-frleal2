#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

#define LED_GREEN BIT6  //P1.6

int redrawScreen = 1;

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
    
    while(!redrawScreen){ //PAUSE CPU IF SCREEN DOESNT NEED UPDATING
      P1OUT &= ~LED_GREEN;// GREEN LED OFF W/O CPU
      or_sr(0x10); //CPU OFF
    }
    P1OUT |= LED_GREEN;
    redrawScreen = 0;
  }
}
void wdt_c_handler(){
  static short count = 0;

  P1OUT |= LED_GREEN;  //GREEN LED WHEN CPU IS ON

  count++;

  if(count == 250 && switch_state == 1){
    firstScreen();
    redrawScreen = 1;
    count = 0;
  }
  
  else if(count == 250 && switch_state == 2){
    secondScreen();
    redrawScreen = 1;
    count = 0;
  }

  else if(count == 5 && switch_state == 3){
    redrawScreen = 1;
    count = 0;
  }
  else if(count == 5 && switch_state == 4){
    redrawScreen = 0;
  }

  P1OUT &= ~LED_GREEN;
}
 

