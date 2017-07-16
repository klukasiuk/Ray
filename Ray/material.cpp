#include "material.h"

#include "world.h"
#include "raytracer.h"

PerfectDiffuse::PerfectDiffuse(RGB c)
{
  color = c;
}

RGB PerfectDiffuse::Shade(RayTracer * tracer , HitInfo hit )
{
	RGB totalcolor;

	for(int i=0 ; i < hit.world->lights.size() ; i++)
	{

		Vec3 inDirection = hit.world->lights[i].pos - hit.HitPoint;

		inDirection.fast_normalize();

		double diffuseFactor = Dot(inDirection , hit.normal);

		if (diffuseFactor < 0) 
		continue;

		if (hit.world->AnyObstacle(hit.HitPoint, hit.world->lights[0].pos))
        continue;

		totalcolor = totalcolor +  hit.world->lights[i].color * color * diffuseFactor;
	}

    return  totalcolor;
}



Phong::Phong()
{
  color = colors::Black;
  diffuseCoeff = 0;
  specular = 0;
  specularExponent = 0;
}


Phong::Phong(RGB c , double dc , double s , double se)
{
 color = c;
 diffuseCoeff = dc;
 specular = s;
 specularExponent = se;
}


RGB Phong::Shade(RayTracer * tracer , HitInfo hit )
{
	RGB totalcolor;
	RGB result;

	Vec3 inDirection;

	double diffuseFactor;
	double phongFactor;


	for(int i=0;i<hit.world->lights.size();i++)
	{

		inDirection = hit.world->lights[i].pos - hit.HitPoint;

		inDirection.fast_normalize();

		diffuseFactor = Dot(inDirection , hit.normal);

		if (diffuseFactor < 0) 
		continue;

		if (hit.world->AnyObstacle(hit.HitPoint, hit.world->lights[0].pos))
        continue;

		result =  hit.world->lights[i].color * color * diffuseFactor * diffuseCoeff;

		phongFactor = PhongFactor(inDirection, hit.normal, hit.ray.dir * -1 ,specularExponent  );

		if (phongFactor != 0)
		result = result + color * specular * phongFactor;

		totalcolor = totalcolor + result;
	}

	return totalcolor;
}



Reflective::Reflective(RGB materialColor, double diffuse, double specular, double exponent, double Reflectivity)
{
  

  double sum = diffuse + Reflectivity;                      // Reflecivity + diffuse musi byæ <= 1

  if( sum > 1.0 )
  {
  diffuse = diffuse / sum;
  Reflectivity = Reflectivity / sum;
  }

  direct.color = materialColor;
  direct.diffuseCoeff = diffuse;
  direct.specular = specular;
  direct.specularExponent = exponent;

  reflectivity = Reflectivity;
  
  reflectionColor = materialColor;                         // Mo¿e byc inny kolor
}


RGB  Reflective::Shade(RayTracer * tracer, HitInfo hit)
{
	Vec3 toCameraDirection = hit.ray.dir.inv();

	RGB radiance = direct.Shade(tracer, hit);

	Vec3 reflectionDirection = reflect(toCameraDirection, hit.normal);

	Ray3 reflectedRay(hit.HitPoint, reflectionDirection);

	radiance = radiance + tracer->CalcColor( reflectedRay, hit.Depth) * reflectionColor * reflectivity;


	return radiance;
}

double PhongFactor(Vec3 inDirection, Vec3 normal, Vec3 toCameraDirection , double specularExponent)
{
Vec3 reflected = reflect(inDirection, normal);

double cosAngle = Dot(reflected ,toCameraDirection);

if (cosAngle <= 0)
return 0;

return pow(cosAngle, specularExponent);
}