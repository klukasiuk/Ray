#include "object.h"


Sphere::Sphere(Vec3 p , double radius , Material * m)
{
 pos = p;

 r = radius;

 material = m;
}

bool Sphere::HitTest(Ray3 ray , double & dist , Vec3 & n)
{
  double t;

  Vec3 distance = ray.pos - pos;

  double a = ray.dir.quad_value();

 // double b = Dot( distance * 2 , ray.dir );       

  double b = 2*distance.x*ray.dir.x + 2*distance.y*ray.dir.y +2*distance.z*ray.dir.z;

  double c = distance.quad_value() - r * r;

  double disc = b * b - 4 * a * c;

  if (disc < 0)    // Delta mniejsza od zera
  return false;


  disc = sqrt(disc);


  t = (-b - disc) / 2*a;

  if (t < epsilon)
  t = (-b + disc) / 2*a;

  if (t < epsilon)
  return false;

  Vec3 hitPoint = (ray.pos + ray.dir * t);

  n = hitPoint - pos;

  n.fast_normalize();

  dist = t;

  return true;
}




//bool Sphere::HitTest(Ray3 ray , double & dist , Vec3 & n)
//{
//  double t;
//
//  Vec3 distance = ray.pos - pos;
//
//  double a = ray.dir.quad_value();
//
//  double b = Dot( distance * 2 , ray.dir );                                   
//
//  double c = distance.quad_value() - r * r;
//
//  double disc = b * b - 4 * a * c;
//
//  if (disc < 0)    // Delta mniejsza od zera
//  return false;
//
//
//  double discSq = sqrt(disc);
//
//  double denom = 2 * a;
//
//  t = (-b - discSq) / denom;
//
//  if (t < epsilon)
//  t = (-b + discSq) / denom;
//
//  if (t < epsilon)
//  return false;
//
//  Vec3 hitPoint = (ray.pos + ray.dir * t);
//
//  n = hitPoint - pos;
//
//  n.fast_normalize();
//
//  dist = t;
//
//  return true;
//}



Plane::Plane(Vec3 p , Vec3 n , Material * m)
{
	point = p;
	normal = n;
	material = m;
}

bool Plane::HitTest(Ray3 ray , double & dist , Vec3 & n)
{
double t =  Dot(point - ray.pos , normal) / Dot(ray.dir,normal);      

if (t > epsilon)
{
n = normal;
dist = t;
return true;
}
return false;
}

Cylinder::Cylinder(Vec3 p , Vec3 d , double R, Material * m)
{
	pos = p;

	dir = d;
	dir.normalize();

	r = R;

	h = 0;

	material = m;
}

Cylinder::Cylinder(Vec3 p , Vec3 d , double R,double H, Material * m)
{
	pos = p;

	dir = d;
	dir.normalize();

	r = R;

	h = H;

	material = m;
}

bool Cylinder::HitTest(Ray3 ray , double & dist , Vec3 & n)
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

  Vec3 point = ray.pos + ray.dir * t;

  Vec3 point2 = dir * Dot(point,dir) + pos;

  if( h != 0 )
  {
	 if ( (point2 - pos).value() > h )
	 return false;
  }


  dist = t;
  n = point - point2;
  n.normalize();

  return true;
}