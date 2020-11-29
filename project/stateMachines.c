#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

unsigned char toggle_led;

void state_init(){
  switch_state = 0;
  toggle_led = LED_GREEN | LED_RED;
  led_update();
}

void state_advance(){
  switch (switch_state){
  case 1:
    toggle_led = LED_GREEN;
    play_note();
    break;
  case 2:
    toggle_led = LED_RED;
    play_note();
    break;
  case 3:
    toggle_led = LED_GREEN | LED_RED;
    play_note();
    break;
  case 4:
    toggle_led = 0;
    play_note();
    break;
  default: break;
  }
  led_update(); //after the state is set it will update the leds accordingly
}