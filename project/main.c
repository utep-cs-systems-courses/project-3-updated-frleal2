#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

int main(){
  state_init();
  configureClocks();
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();
  
  or_sr(0x18);
}
