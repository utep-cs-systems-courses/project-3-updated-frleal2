#include <msp430.h>
#include <libTimer.h>
#include <lcdutil.h>
#include <lcddraw.h>
#include <shape.h>
#include <abCircle.h>
#include "pac_shape.h"
#include <chordVec.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "movementB.h"
#include <stdlib.h>
#include "scorer.h"
#include "cheater.h"

#define GREEN_LED BIT6

Pac_Man pacman = {abCircleGetBounds, pac_man_check, chordVec10, 10};
AbCircle target = {abCircleGetBounds, abCircleCheck, chordVec5, 5};
AbCircle ammo = {abCircleGetBounds, abCirclecheck, chordVec2, 2};

//Playing field
AbRectOutline fieldOutline = {
  abRectOutlineGetBounds, abRectOutlineCheck,{screenWidth/2 - 10, screenHeight/2 - 10}
};

//Playing field as a layer
Layer fieldLayer = {
  (AbShape *) &fieldOutline,
  {screenWidth/2, screenHeight/2}, //center
  {0,0},{0,0}, //last & next position
  COLOR_BLACK,
};

//layer with the shooting pacman
Layer layer3 = {
  (AbShape *) &pacman,
  {+40, screenHeight-20}, //bottom left corner
  {0,0},{0,0}, //last and next position
  COLOR_YELLOW,
  &fieldLayer
};

Layer layer2 = {
  (AbShape *) &target,
  {+20, +15}, //top left corner
  {0,0},{0,0},
  COLOR_RED,
  &fieldLayer,
};

Layer layer1 = {
  (AbShape *) &ammo,
  {+40, screenHeight-20},
  {0,0},{0,0},
  COLOR_BLUE,
  &fieldLayer,
};

MovLayer ml3 = { &layer3, {0,0}, 0}; //pacaman moves horizontally
MovLayer ml2 = { &layer2, {0,0}, 0}; //target moves horizontally
MovLayer ml1 = { &layer1, {0,3}, 0}; //vertical movement

u_int bgColor = COLOR_BLACK; //BACKGROUND COLOR
int redrawScreen = 1; //boolean to redraw screen

Region fieldFence; //fence for playing field

void restoreGame(MovLayer *mlP){
  score = 0;
  layer3.pos.axes[0] = +40;
  layer3.pos.axes[1] = screenHeight-20;
  layer2.pos.axes[0] = +20;
  layer2.pos.axes[0] = +15;
  layerInit(&layer3);
  layerInit(&layer2);
  layerDraw(&layer3);
  layerDraw(&layer2);
}




int main(){
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  
  configureClocks(); 
  switch_init();
  led_init();
  buzzer_init();
  state_init();
  enableWDTInterrupts();
  lcd_init();
  shapeInit();
  layerInit(&layer3);
  layerDraw(&layer3);
  layerInit(&layer2);
  layerDraw(&layer2);

  layerGetBounds(&fieldLayer, &fieldFence);

  or_sr(0x18);

  while(true){
    while(!redrawScreen){
      P1OUT &= ~GREEN_LED;
      or_sr(0x18);
    }
    P1OUT |= GREEN_LED;
    redrawScreen = 0;
    movLayerDraw(&ml3, &layer3);
    movLayerDraw(&ml2, &layer2);
    scoreUp();
    if(score == 3){
      restoreGame(&ml2);
    }
    drawString54x7(screenWidth-80,0,"Score", COLOR_RED, COLOR_YELLOW);
  }
}
void wdt_c_handler(){
  static short count = 0;
  P1OUT |= GREEN_LED;
  count ++;
  if(count == 15){
    mlAdvanceSh(&ml2, &fieldFence, &m13);
    redrawScreen = 1;
    count = 0;
  }
  if(count>15) count = 0;
  P1OUT &= ~GREEN_LED;
}

