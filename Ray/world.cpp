#include "world.h"
#include <math.h>

World::World(RGB c)
{
 background = c;
}

void World::AddObject(Object * obj)
{
 objects.push_back(obj);
}

void World::AddLight(PointLight  light)
{
 lights.push_back(light);
}

 HitInfo World::TraceRay(Ray3 ray)
  {
	HitInfo result;
	Vec3 normal;

	result.HitObject = NULL;

	double minimalDistance = infinity;       // najbli¿sze trafienie
    double lastDistance = 0;                  // zmienna pomocnicza, ostatnia odleg³oœæ

	for(int i=0;i<objects.size();i++)
	{
		  if(objects[i]->HitTest(ray,lastDistance,normal) )
		  if(lastDistance < minimalDistance)
		  {
			minimalDistance = lastDistance;
			result.HitObject  = objects[i];
			result.normal  = normal;
		  }
	}

	if(result.HitObject != NULL)
	{
        result.HitPoint = ray.pos + ray.dir * minimalDistance;
		result.ray = ray;
		result.dist = minimalDistance;
		result.world = this;
	}

	return result;
  }


 bool World::AnyObstacle(Vec3 A, Vec3 B)
{
// odleg³oœæ od cieniowanego punktu do œwiat³a
Vec3 vectorAB = B - A;


double distAB = vectorAB.value();

double currDistance = infinity;

// promieñ (pó³prosta) z cieniowanego punktu w kierunku œwiat³a
Ray3 ray(A, vectorAB);

Vec3 ignored;

for(int i=0;i<objects.size();i++)       
{
// jeœli jakiœ obiekt jest na drodze promienia oraz trafienie
// nast¹pi³o bli¿ej ni¿ odleg³oœæ punktu do œwiat³a,
// obiekt jest w cieniu
if (objects[i]->HitTest(ray, currDistance, ignored) && currDistance < distAB)
return true;

}


return false;
}