#include "movementB.h"
#include <shape.h>
#include <sr.h>
#include "scorer.h"
#include "buzzer.h"

static char counter; //static counter to traverse our pseudorandom list
static char nums[25] = {25,62,100,35,87,59,89,112,74,20,83,111,
                        50,15,98,67,38,14,56,80,39,103,90,19,48}; //pseudorandom list

void movLayerDraw(MovLayer *movLayers, Layer *layers)
{
  int row, col;
  MovLayer *movLayer;

  and_sr(~8);			/**< disable interrupts (GIE off) */
  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Layer *l = movLayer->layer;
    l->posLast = l->pos;
    l->pos = l->posNext;
  }
  or_sr(8);			/**< disable interrupts (GIE on) */

  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Region bounds;
    layerGetBounds(movLayer->layer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1], 
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	Layer *probeLayer;
	for (probeLayer = layers; probeLayer; 
	     probeLayer = probeLayer->next) { /* probe all layers, in order */
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break; 
	  } /* if probe check */
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for moving layer being updated
}	  

/**Checks for collision with shape for both axes separately to avoid double checking*/
u_char collision(Vec2 *shapePos, Region *shapeBound){
   if(shapePos->axes[0] < (shapeBound->topLeft.axes[0]) || shapePos->axes[0] > (shapeBound->botRight.axes[0]))
      return 0;
   if(shapePos->axes[1] < (shapeBound->topLeft.axes[1]) || shapePos->axes[1] > (shapeBound->botRight.axes[1]))
      return 0;
   return 1;
}

/** Advances a moving shape within a fence and also checking for acollision with another shape
 *  
 *  \param ml The moving shape to be advanced
 *  \param fence The region which will serve as a boundary for ml
 *  \param ml2 the other shape to be considered for collision
 */
void mlAdvanceSh(MovLayer *ml, Region *fence, MovLayer *ml2)
{
  Vec2 newPos; //new position for after collision
  u_char axis;
  Region shapeBoundary; //boundary of first shape
  Region shapeBoundary2; //boundary of second shape
  Vec2 posBall; //current position of shape one
  layerGetBounds(ml2->layer,&shapeBoundary2); //bounds of secnd shape
  for (; ml; ml = ml->next) {
    posBall = ml->layer->pos; //current position of current ball
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for (axis = 0; axis < 2; axis ++) {
      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {
	newPos.axes[0] = ml->layer->pos.axes[0];
	newPos.axes[1] = 20;
      }	/**< if outside of fence */
    } /**< for axis */
    if(collision(&posBall, &shapeBoundary2)){ //if collides with other shape
      newPos.axes[0] = screenWidth-nums[counter]; //sets new position to a new "random" place so you have to chase it
      counter++; //adds to counter
      if(counter>24) //reset counter
	counter = 0;
      newPos.axes[1] = 20;
      scoreChanged = 1; //notice about a need to change score
      buzzer_set_period(200); //make sound
    } //if collides with other shape
    ml->layer->posNext = newPos;
  } /**< for ml */
}

/*Same as previous but does not check for other shape colliding and advances shape to opposite side as speed given*/
void mlAdvanceOpp(MovLayer *ml, Region *fence){
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  ml->velocity.axes[0] = -ml->velocity.axes[0];
  for(;ml;ml = ml->next){
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for(axis = 0; axis<2; axis++){
      if((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	 (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis])){
	int velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];
	newPos.axes[axis] += (2*velocity);
	buzzer_set_period(2000); //make sound when bounce against wall
      }//if outside of fence
    }//for axis 
    ml->layer->posNext = newPos;
  }//for ml
}

/*Same as previous but advances figure without cheecking for collision with different shape,*/
void mlAdvance(MovLayer *ml, Region *fence){
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  for(;ml;ml = ml->next){
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for(axis = 0; axis<2; axis++){
      if((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	 (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis])){
	int velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];
	newPos.axes[axis] += (2*velocity);
	buzzer_set_period(2000); //make sound when bounce against wall
      }//if outside of fence
    }//for axis 
    ml->layer->posNext = newPos;
  }//for ml
}

