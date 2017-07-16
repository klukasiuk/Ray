#include "color.h"

//RGB

// Konstruktory

RGB::RGB()
{
 r=0;
 g=0;
 b=0;
}

RGB::RGB(double R , double G , double B)
{
 clamp(R,0,255);
 clamp(G,0,255);
 clamp(B,0,255);


 r=R;
 g=G;
 b=B;
}

// Operatory

RGB RGB::operator +(RGB c)
{
  return RGB(r + c.r , g + c.g , b + c.b);
}

RGB RGB::operator *(RGB c)
{
  return RGB(255 * (r/255.0) * (c.r/255.0) , 255 * (g/255.0) * (c.g/255.0) , 255 * (b/255.0) * (c.b/255.0));
}

RGB RGB::operator *(double s)
{
  return RGB(r * s , g * s , b * s);
}

namespace colors
{
  RGB Black(0,0,0);
  RGB White(255,255,255);

  RGB Red(255,0,0);
  RGB Green(0,255,0);
  RGB Blue(0,0,255);

  RGB LightRed(255,50,50);
  RGB LightGreen(50,255,50);
  RGB LightBlue(50,50,255);

  RGB Yellow(255,255,0);
  RGB Magenta(255,0,255);
  RGB Cyan(0,255,255);

  RGB Sky(135,206,235);

  RGB DarkGrey(120,120,120);
  RGB LightGrey(180,180,180);
};



