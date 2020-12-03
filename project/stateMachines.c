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
void firstScreen(){ //This will draw mario traversing through the plane 
  static char color = 1;

  switch(color){
  case 1:
    fillRectangle(2, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(125, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);
    
  
    color++;
    break;
  case 2:
    fillRectangle(125, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(65, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);
    

    color++;
    break;
  case 3:
    fillRectangle(65, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(35, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);


    color++;
    break;
  case 4:
    fillRectangle(35, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(2, 75, 10, 10, COLOR_BROWN);
    drawMario(10,100, COLOR_WHITE);

    
    play_note();
    color = 1;
    break;
  default: break;
  }  
}

void secondScreen(){ //This will draw LUIGI traversing through the plane 
  static char color = 1;

  switch(color){
  case 1:
    fillRectangle(2, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME LUIGI!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(125, 75, 10, 10, COLOR_BROWN);
    drawLuigi(10,100, COLOR_WHITE);
    
  
    color++;
    break;
  case 2:
    fillRectangle(125, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME LUIGI!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(65, 75, 10, 10, COLOR_BROWN);
    drawLuigi(10,100, COLOR_WHITE);
    

    color++;
    break;
  case 3:
    fillRectangle(65, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME LUIGI!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(35, 75, 10, 10, COLOR_BROWN);
    drawLuigi(10,100, COLOR_WHITE);


    color++;
    break;
  case 4:
    fillRectangle(35, 75, 10, 10, COLOR_WHITE);
    drawString5x7(10,20, "IT'S ME LUIGI!", COLOR_RED, COLOR_WHITE);
    fillRectangle(0, 120, 150, 60, COLOR_GREEN);
    fillRectangle(2, 75, 10, 10, COLOR_BROWN);
    drawLuigi(10,100, COLOR_WHITE);
  
    
    play_note();
    color = 1;
    break;
  default: break;
  }  
}


void state_advance(){
  
  switch (switch_state){
  case 1:
    clearScreen(COLOR_WHITE);
    firstScreen(); 
    toggle_led = LED_RED;
    play_note();
    break;
  case 2:
    clearScreen(COLOR_WHITE);
    secondScreen();
    toggle_led = LED_RED;
    play_note();
    break;
  case 3:
    clearScreen(COLOR_BLACK);
    drawString5x7(0,0,"WEAR YOUR FACEMASK!", COLOR_RED, COLOR_BLACK);
    toggle_led = LED_GREEN | LED_RED;
    toggle_led = 0;
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
