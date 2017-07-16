#pragma once

#include <cmath>  // sqrt()

const double epsilon = 0.00001;

const double infinity = 1.7976931348623158e+308;


struct Vec3
{
  double x;
  double y;
  double z;


  Vec3();
  Vec3(double X , double Y , double Z);


  Vec3 operator +(Vec3 b);
  Vec3 operator -(Vec3 b);

  Vec3 operator *(double s);
  Vec3 operator /(double s);

  Vec3 inv();


  void rotate(Vec3 axis , double angle);


  double value();
  double quad_value();
  
  void normalize();
  void fast_normalize();
};

struct Ray3
{
	Vec3 pos;
	Vec3 dir;


	Ray3();
	Ray3(Vec3 p , Vec3 d);
};


struct Mat3
{
	double data[9];


	Mat3();
};

struct Mat4
{
    double data[16];


	Mat4();
};

struct Quaternion
{
 double x;
 double y;
 double z;
 double w;

 Quaternion();
 Quaternion(Vec3 axis , double angle);

 double value();
 double quad_value();

 void normalize();
 void fast_normalize();

 Quaternion conjugate();

 Quaternion operator *(Quaternion a);

};


 double Dot(Vec3 A , Vec3 B);

 Vec3 Cross(Vec3 A , Vec3 B);

 Vec3 reflect(Vec3 vec , Vec3 normal);


void clamp(double & val , double a , double b);


float FastInvSqrt(float number);