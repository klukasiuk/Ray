#pragma once

#include "material.h"


class Object
{
  public:

  Material * material;

  virtual bool HitTest(Ray3 ray , double & dist , Vec3 & n ) = 0;

};

class Sphere : public Object
{
public:
  double r;

  Vec3 pos;

  Sphere(Vec3 p , double radius , Material * m );

  bool HitTest(Ray3 ray , double & dist , Vec3 & n);
};


class Plane : public Object
{
public:
  Vec3 point;

  Vec3 normal;

  Plane(Vec3 p , Vec3 n ,  Material * m);

  bool HitTest(Ray3 ray , double & dist , Vec3 & n );
};

class Cylinder : public Object
{
public:
  Vec3 pos;

  Vec3 dir;

  double r;

  double h;

  Cylinder(Vec3 p , Vec3 d , double R , Material * m);
  Cylinder(Vec3 p , Vec3 d , double R , double H , Material * m);

  bool HitTest(Ray3 ray , double & dist , Vec3 & n );
};


//
//class Triangle : public Object
//{
// Vec3 vert[3];
//};