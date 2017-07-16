#pragma once

#include <vector>

#include "object.h"
#include "light.h"

using std::vector;


class World
{
  public:


  RGB background;

  vector<Object *> objects;
  vector<PointLight> lights;


  World(){};

  World(RGB b);

  void AddObject(Object * ob);
  void AddLight(PointLight light);

  HitInfo TraceRay(Ray3 ray);

  bool AnyObstacle(Vec3 A , Vec3 B);
};