#pragma once

#include "camera.h"
#include "world.h"
#include "framebuffer.h"

class RayTracer
{
public:
  Camera * camera;

  World world;

  bool draw_depth;

  FrameBuffer * framebuffer;

  int maxdepth;


  RayTracer(Camera * cam , World w , FrameBuffer * f );
 ~RayTracer();

  void Trace();

  void MultiTrace();

  RGB CalcColor(Ray3 ray , int currentdepth);

  bool AnyObstacle(Vec3 A , Vec3 B);
};

