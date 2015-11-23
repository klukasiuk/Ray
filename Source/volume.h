#pragma once

#include "camera.h"
#include "world.h"
#include "framebuffer.h"



class VolumeRenderer
{
  public:

  Camera * camera;

  World * world;

  FrameBuffer * framebuffer;

  RGB ** normal_map;


  VolumeRenderer(Camera * cam , World * w , FrameBuffer * f );

  void Render();

};