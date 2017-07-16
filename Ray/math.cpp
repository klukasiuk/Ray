#include "math.h"


// Vec3

// Konstruktory

Vec3::Vec3()
{
 x = 0.0 ;
 y = 0.0 ;
 z = 0.0 ;
}

Vec3::Vec3(double X , double Y , double Z)
{
 x = X;
 y = Y ;
 z = Z ;
}

// Operatory

Vec3 Vec3::operator +(Vec3 b)
{
 return Vec3(x+b.x,y+b.y,z+b.z);
}

Vec3 Vec3::operator -(Vec3 b)
{
 return Vec3(x-b.x,y-b.y,z-b.z);
}

Vec3 Vec3::operator *(double s)
{
 return Vec3(x*s,y*s,z*s);
}

Vec3 Vec3::operator /(double s)
{
 return Vec3(x/s,y/s,z/s);
}

// Metody

Vec3 Vec3::inv()
{
  return Vec3(-x,-y,-z);
}

void Vec3::rotate(Vec3 axis , double angle)
{
  Quaternion a;

  a.x = x;
  a.y = y;
  a.z = z;
  a.w = 0;

  Quaternion b(axis,angle);

  Quaternion c = b * a * b.conjugate() ;

  x = c.x;
  y = c.y;
  z = c.z;
};


  
double Vec3::value()
{
	return sqrt(x*x + y*y + z*z );
}

double Vec3::quad_value()
{
	return x*x + y*y + z*z ;
}

void Vec3::normalize()
{
	*this = *this * 1/this->value() ;
}

void Vec3::fast_normalize()
{
  *this = *this * FastInvSqrt(quad_value());
}


// Ray3

// Kostruktory

Ray3::Ray3()                                               // Pusty poniewa¿ wektory maj¹ w³asne konstruktory
{

}

Ray3::Ray3(Vec3 p , Vec3 d)
{
	pos = p;
	dir = d;

	dir.fast_normalize();                            // Kierunek musi byæ znormalizowany
}


// Mat3

// Konstruktory 

Mat3::Mat3()
{
  for(int i=0;i<9;i++)
  data[i]=0;
}


// Mat4

// Konstruktory 

Mat4::Mat4()
{
  for(int i=0;i<16;i++)
  data[i]=0;
}


// Quaternion

// Konstruktory 

Quaternion::Quaternion()
{
 x = 0;
 y = 0;
 z = 0;
 w = 0;
}

Quaternion::Quaternion(Vec3 axis , double angle)
{
 double sinus = sin(angle/2);

 x = axis.x * sinus;
 y = axis.y * sinus;
 z = axis.z * sinus;
 w = cos(angle/2);
}

// Metody
double Quaternion::value()
{
  return sqrt(x*x + y*y + z*z + w*w);
}

double Quaternion::quad_value()
{
  return x*x + y*y + z*z + w*w ;
}

void Quaternion::normalize()
{
double val = ( 1 / value() );

 w = w * val;
 x = x * val;
 y = y * val;
 z = z * val;
}

 void Quaternion::fast_normalize()
 {
   double val = FastInvSqrt( quad_value() );

    w = w * val;
    x = x * val;
    y = y * val;
    z = z * val;
 }

 Quaternion Quaternion::conjugate()
 {
  Quaternion q;

  q.w = w;
  q.x = -x;
  q.y = -y;
  q.z = -z;

  return q;
 }

 Quaternion Quaternion::operator *(Quaternion B)
 {
  Quaternion C;

  C.x = w*B.x + x*B.w + y*B.z - z*B.y;
  C.y = w*B.y - x*B.z + y*B.w + z*B.x;
  C.z = w*B.z + x*B.y - y*B.x + z*B.w;
  C.w = w*B.w - x*B.x - y*B.y - z*B.z;

  return C;
 }


// Funkcje

double Dot(Vec3 A , Vec3 B)                           // Iloczyn skalarny
{
  return A.x*B.x + A.y*B.y + A.z*B.z ;
}

Vec3 Cross(Vec3 A , Vec3 B)                           // Iloczyn wektorowy
{
  return Vec3( A.y * B.z - A.z * B.y,
               A.z * B.x - A.x * B.z,
               A.x * B.y - A.y * B.x  );
}

Vec3 reflect(Vec3 vec, Vec3 normal)
{
double dot = Dot(vec,normal);

return normal * dot * 2 - vec;
}




void clamp(double & val , double a , double b)
{
	if( val < a)
	{
    val = a;
	return;
	}

	if( val > b)
	val = b;
}


float FastInvSqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
 
	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
 
	return y;
}