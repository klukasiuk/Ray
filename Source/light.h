#pragma once 

#include "color.h"
#include "math.h"




class PointLight
{
  public:

  Vec3 pos;

  RGB color;

  PointLight( Vec3 p , RGB c ) : pos(p) , color(c) {};
};



class Directional
{
  public:

  Vec3 dir;

  RGB color;

  Directional( Vec3 d , RGB c ) : dir(d) , color(c) {};
};