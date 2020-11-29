#include <msp430.h>
#include <libTimer.h>
#include "buzzer.h"

void buzzer_init(){




  timerAUpmode(); //DRIVE TO SPEAKER 
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // ENABLE OUTPUT TO SPEAKE
}

void buzzer_set_period(shor cycles){ // THIS WILL MAKE A BEEP NOISE DEPENDING ON THE CYCLES THAT ARE GIVEN IN THE FOR
  for(int i = 0; i< 16000; i++){
    CCR0 = cycles;
    CCR1 = cycles >> 1;
  }
  CCR0 = 0;
  CCR1 = 0;
}
  
