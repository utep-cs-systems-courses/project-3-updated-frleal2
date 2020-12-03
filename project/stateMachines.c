#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

unsigned char toggle_led;

void state_init(){
  
  switch_state = 0;
  toggle_led = LED_GREEN | LED_RED;
  led_update();
}
void firstScreen(){
  static char color = 1;

  switch(color){
  case 1:
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(75, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);
     
    toggle_led = LED_GREEN;
    play_note();
    color++;
    break;
  case 2:
    clearScreen(COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(60, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);
    
    toggle_led = LED_RED;
    play_note();
    color++;
    break;
  case 3:
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(45, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);
    
    toggle_led = LED_GREEN | LED_RED;
    play_note();
    color++;
    break;
  case 4:
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(30, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);
    
    toggle_led = 0;
    play_note();
    color = 1;
    break;
  default: break;
  }  
}

void state_advance(){
  
  switch (switch_state){
  case 1:
    firstScreen(); 
    toggle_led = LED_GREEN;
    play_note();
    break;
  case 2:
    // drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    // fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    // fillRectangle(60, 75, 10, 10, COLOR_BROWN);
    // drawMario(10,100, COLOR_WHITE);
    
    toggle_led = LED_RED;
    play_note();
    break;
  case 3:
    //drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    //fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    //fillRectangle(45, 75, 10, 10, COLOR_BROWN);
    //drawMario(10,100, COLOR_WHITE);
    
    toggle_led = LED_GREEN | LED_RED;
    play_note();
    break;
  case 4:
    //drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    // fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    // fillRectangle(20, 75, 10, 10, COLOR_BROWN);
    //drawMario(10,100, COLOR_WHITE);
    
    toggle_led = 0;
    play_note();
    break;
  default: break;
  }
  led_update(); //after the state is set it will update the leds accordingly
}
