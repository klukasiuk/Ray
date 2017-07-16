#pragma once

#include "math.h"

class World;
class Object;

struct HitInfo
{
  Object * HitObject ;

  World * world ;

  Vec3 normal;

  Vec3 HitPoint;

  Ray3 ray;

  double dist;

  int Depth;
};