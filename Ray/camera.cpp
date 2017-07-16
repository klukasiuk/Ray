#include "camera.h"


Ortho::Ortho(double x , double y , Vec3 p , Vec3 d , Vec3 u)
{
 width = x;
 height = y;

 pos = p;
 dir = d;
 up = u;

 up.normalize();
 dir.normalize();

 right = Cross(dir,up);

 right.normalize();

 up = Cross(right,dir);

 up.normalize();
}

void Ortho::rotateX(double a)
{
   dir.rotate(right, -a);

   right.fast_normalize();

   up = Cross(right,dir);

   up.fast_normalize();
}

void Ortho::rotateY(double a)
{
  dir.rotate(Vec3(0,1,0),a);

  dir.fast_normalize();

  up.rotate(Vec3(0,1,0),a);

  up.fast_normalize();

  right = Cross(dir,up);

  right.fast_normalize();
}

Ray3 Ortho::GetRay(double x , double y)
{
	Ray3 ray;

	ray.dir = dir;                             // Kierunek taki sam jak kamery

	ray.pos = pos + right *(width * 0.5 * x) + up *(height * 0.5 * y); 

	return ray;
}


  Persp::Persp(double x , double y , double F , Vec3 p , Vec3 d , Vec3 u)
  {
	width = x;
	height = y;

	f = F;

	pos = p;

	dir = d;

	up = u;


	dir.normalize();

	up.normalize();

	right = Cross(dir,up);

	right.normalize();

	up = Cross(right,dir);

    up.normalize();

  }

  void Persp::rotateX(double a)
  {
   dir.rotate(right, -a);

   right.fast_normalize();

   up = Cross(right,dir);

   up.fast_normalize();
  }

void Persp::rotateY(double a)
{
  dir.rotate(Vec3(0,1,0),a);

  dir.fast_normalize();

  up.rotate(Vec3(0,1,0),a);

  up.fast_normalize();

  right = Cross(dir,up);

  right.fast_normalize();
}

  Ray3 Persp::GetRay(double x , double y)
  {
	Ray3 ray;

	ray.pos = pos;

    Vec3 point = pos + dir*f + right *(width * 0.5 * x) + up *(height * 0.5 * y);   //Punkt na rzutni

	ray.dir = point - pos;

	ray.dir.fast_normalize();
	//ray.dir.normalize();

	return ray;
  }