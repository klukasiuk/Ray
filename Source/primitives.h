#pragma once

#include "math.h"

class Primitive
{
  public:
  virtual bool HitTest(Ray3 ray , double & dist ) = 0;

};

class Sphere : public Primitive
{
public:
  double r;

  Vec3 pos;

  Sphere(Vec3 p , double radius );

  bool HitTest(Ray3 ray , double & dist );
};


class Plane : public Primitive
{
public:
  Vec3 point;

  Vec3 normal;

  Plane(Vec3 p , Vec3 n);

  bool HitTest(Ray3 ray , double & dist );
};

class Cylinder : public Primitive
{
public:
  Vec3 pos;

  Vec3 dir;

  double r;

  Cylinder(Vec3 p , Vec3 d , double R);

  bool HitTest(Ray3 ray , double & dist );
};


//
//class Triangle : public Primitive
//{
// Vec3 vert[3];
//};