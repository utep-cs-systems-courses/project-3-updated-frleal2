#ifndef pac_shape_included
#define pac_shape_included

#include <shape.h>
#include "./../circleLib/_abCircle.h"

//struct to create a pacman

typedef struct Pac_s{
  void(*getBounds) (const struct AbCircle_s *circle, const Vec2 *centerPos, Region *bounds);
  int (*check)(const struct AbCircle_s *circle, const Vec2 *centerPos, const Vec2 *pixel);
  const u_char *chords;
  const u_char radius;
} Pac_Man;

//This is to create a sliced circle

int pac_man_check(const AbCircle *circle, const Vec2 *circlePos, const Vec2 *pixel);

#endif
