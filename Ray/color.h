#pragma once
#include "math.h"

struct RGB
{
  double r;
  double g;
  double b;

  RGB();
  RGB(double R , double G , double B);

  RGB operator +(RGB c);
  RGB operator *(RGB c);
  RGB operator *(double s);

};

namespace colors
{
 extern RGB Black;
 extern RGB White;

 extern RGB Red;
 extern RGB Green;
 extern RGB Blue;

 extern RGB LightRed;
 extern RGB LightGreen;
 extern RGB LightBlue;

 extern RGB Yellow;
 extern RGB Magenta;
 extern RGB Cyan;

 extern RGB Sky;

 extern RGB DarkGrey;
 extern RGB LightGrey;
};