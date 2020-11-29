#ifndef movementB_included
#define movementB_included

#include "./../shapeLib/shape.h"


/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

/*Method to draw moving layer*/
void movLayerDraw(MovLayer *movLayers, Layer *layers);

/*method to advance shape */
void mlAdvance(MovLayer *m1, Region *fence);
/*Method to advance opposite side*/
void mlAdvanceOpp(MovLayer *ml, Region *fence);
/*Method to advance shape with collision with other shape*/
void mlAdvanceSh(MovLayer *ml, Region *fence, MovLayer *ml3);

#endif
