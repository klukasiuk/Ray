#pragma once

#include "math.h"

class Camera
{
 public:

  Vec3 pos;                           // Pozycja kamery

  Vec3 dir;                           // Kierunek widzenia

  Vec3 up;                            // Kierunek w górê 

  Vec3 right;                         // Kierunek w prawo

  double width;                       // Wymiary rzutni
  double height;

  virtual void rotateX(double a) = 0;
  virtual void rotateY(double a) = 0;


 virtual Ray3 GetRay(double x , double y) = 0;     // Zwraca promieñ przebiegaj¹cy przez konkretny pixel 
};                                                 // Wartoœci < -1.0 ; 1.0 >




class Ortho : public Camera
{
  public:

  void rotateX(double a);

  void rotateY(double a);

  Ortho(double x , double y , Vec3 p , Vec3 d , Vec3 u);

  Ray3 GetRay(double x , double y); 
};


class Persp : public Camera
{
  public:

  double f;                           // Ogniskowa

  void rotateX(double a);
  void rotateY(double a);

  Persp(double x , double y , double f , Vec3 p , Vec3 d , Vec3 u);

  Ray3 GetRay(double x , double y); 
};



