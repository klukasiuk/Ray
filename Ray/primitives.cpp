#include "primitives.h"

Sphere::Sphere(Vec3 p , double radius )
{
 pos = p;

 r = radius;
}

bool Sphere::HitTest(Ray3 ray , double & dist)
{
  double t;

  Vec3 distance = ray.pos - pos;

  double a = ray.dir.quad_value();

  double b = Dot( distance * 2 , ray.dir );                                   

  double c = distance.quad_value() - r * r;

  double disc = b * b - 4 * a * c;

  if (disc < 0)    // Delta mniejsza od zera
  return false;


  double discSq = sqrt(disc);

  double denom = 2 * a;

  t = (-b - discSq) / denom;

  if (t < epsilon)
  t = (-b + discSq) / denom;

  if (t < epsilon)
  return false;


  dist = t;
  return true;
}

Plane::Plane(Vec3 p , Vec3 n)
{
	point = p;
	normal = n;
}

bool Plane::HitTest(Ray3 ray , double & dist)
{
double t =  Dot(point - ray.pos , normal) / Dot(ray.dir,normal);      

if (t > epsilon)
{
dist = t;
return true;
}
return false;
}

Cylinder::Cylinder(Vec3 p , Vec3 d , double R)
{
	pos = p;
	dir = d;
	r = R;
}

bool Cylinder::HitTest(Ray3 ray , double & dist)
{
  Vec3 dPos = ray.pos - pos;

  double t;

  double A = (ray.dir - dir*Dot(ray.dir,dir) ).quad_value() ;
  double B = 2 * Dot( ray.dir - dir*Dot(ray.dir,dir) , dPos - dir*Dot(dPos,dir) );
  double C = ( dPos - dir*Dot(dPos,dir) ).quad_value() - r*r;


  double disc = B * B - 4 * A * C;

  if (disc < 0)    // Delta mniejsza od zera
  return false;


  double discSq = sqrt(disc);

  double denom = 2 * A;

  t = (-B - discSq) / denom;

  if (t < epsilon)
  t = (-B + discSq) / denom;

  if (t < epsilon)
  return false;


  dist = t;
  return true;
}