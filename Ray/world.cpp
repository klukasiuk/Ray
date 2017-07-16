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

	double minimalDistance = infinity;       // najbli�sze trafienie
    double lastDistance = 0;                  // zmienna pomocnicza, ostatnia odleg�o��

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
// odleg�o�� od cieniowanego punktu do �wiat�a
Vec3 vectorAB = B - A;


double distAB = vectorAB.value();

double currDistance = infinity;

// promie� (p�prosta) z cieniowanego punktu w kierunku �wiat�a
Ray3 ray(A, vectorAB);

Vec3 ignored;

for(int i=0;i<objects.size();i++)       
{
// je�li jaki� obiekt jest na drodze promienia oraz trafienie
// nast�pi�o bli�ej ni� odleg�o�� punktu do �wiat�a,
// obiekt jest w cieniu
if (objects[i]->HitTest(ray, currDistance, ignored) && currDistance < distAB)
return true;

}


return false;
}