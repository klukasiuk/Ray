#pragma once

#include "hitinfo.h"
#include "color.h"

class RayTracer;
class World;

class Material
{
    public:

	virtual RGB Shade(RayTracer * tracer , HitInfo hit ) = 0;
};


class PerfectDiffuse : public Material
{
    public:

	RGB color;

	PerfectDiffuse(RGB c);

	RGB Shade(RayTracer * tracer , HitInfo hit );
};


class Phong : public Material
{
  public:

  RGB color;

  double diffuseCoeff;
  double specular;
  double specularExponent;

  Phong();
  Phong(RGB c , double dc , double s , double se);

  RGB Shade(RayTracer * tracer , HitInfo hit );
};


//class Chessboard : public Material
//{
//  public:
//
//  RGB color1;
//  RGB color2;
//
//  double size;
//
//
//  double diffuseCoeff;
//  double specular;
//  double specularExponent;
//
//  Chessboard(RGB c1 , RGB c2 , double a, double dc, double s , double se);
//
//  RGB Shade(RayTracer * tracer , HitInfo hit );
//};

class Reflective : public Material
{
   Phong direct; // do bezpoœredniego oœwietlenia

   double reflectivity;

   RGB reflectionColor;

   public :

   Reflective(RGB materialColor, double diffuse, double specular, double exponent, double reflectivity);

   RGB Shade(RayTracer * tracer , HitInfo hit );
};

double PhongFactor(Vec3 inDirection, Vec3 normal, Vec3 toCameraDirection , double specularExponent);