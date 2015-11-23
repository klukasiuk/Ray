#include"raytracer.h"


RayTracer::RayTracer(Camera * cam , World w , FrameBuffer * f )
{
  camera  = cam;

  world = w;

  draw_depth = true;

  framebuffer = f;

  maxdepth = 2;
}

RayTracer::~RayTracer()
{
  for(int i=0;i<world.objects.size();i++)
  delete world.objects[i];
}

void RayTracer::Trace()
{
  double pic_x;
  double pic_y;

   for(int x = 0; x < framebuffer->width; x++)
   for(int y = 0; y < framebuffer->height; y++)
   {
                                                                         // przeskalowanie x i y do zakresu [-1; 1]
      pic_x = ((x + 0.5) / (double)framebuffer->width) * 2 - 1 ;
      pic_y = ((y + 0.5) / (double)framebuffer->height) * 2 - 1;
                                                                         // wys³anie promienia i sprawdzenie w co w³aœciwie trafi³
      Ray3 ray = camera->GetRay(pic_x,pic_y);                            

	  RGB final = CalcColor(ray , 0);
                                                                         // ustawienie odpowiedniego koloru w obrazie wynikowym
      framebuffer->setpixel(x, y, final );
   }
}

void RayTracer::MultiTrace()
{
  #pragma omp parallel
   {
	  double pic_x;
	  double pic_y;

	  RGB pix;

	  Ray3 ray;

	  int width = framebuffer->width;
	  int height = framebuffer->height;

	  double dw = (double)framebuffer->width;
	  double dh = (double)framebuffer->height;

	   #pragma omp for
      for(int x = 0; x < framebuffer->width; x++)
      for(int y = 0; y < framebuffer->height; y++)
      {
                                                                         // przeskalowanie x i y do zakresu [-1; 1]
        pic_x = ((x + 0.5) / dw) * 2 - 1 ;
        pic_y = ((y + 0.5) / dh) * 2 - 1;

		ray = camera->GetRay(pic_x,pic_y); 
                                                                         // wys³anie promienia i sprawdzenie w co w³aœciwie trafi³
	    pix = CalcColor(ray , 0);
                                                                         // ustawienie odpowiedniego koloru w obrazie wynikowym
        framebuffer->setpixel(x, y, pix );
      }
   }
}


RGB RayTracer::CalcColor(Ray3 ray , int currentdepth)
{
  if( currentdepth > maxdepth )
  return colors::Black;

  HitInfo info = world.TraceRay(ray);

  if(!draw_depth)
  {

	  info.Depth = currentdepth + 1;

	  if (info.HitObject == NULL) 
	  return world.background;

	  RGB finalColor = info.HitObject->material->Shade( this , info);

     return finalColor;
  }
  else
  {
	double fog;

	RGB depth(255,255,255);

    if(info.dist < 50.0 )
    fog =  1 - (info.dist) / (50.0)   ;
    else
    fog = 0;

	depth = depth * fog;

	return depth;
  }
}

bool RayTracer::AnyObstacle(Vec3 A, Vec3 B)
{
// odleg³oœæ od cieniowanego punktu do œwiat³a
Vec3 vectorAB = B - A;


double distAB = vectorAB.value();

double currDistance = infinity;

// promieñ (pó³prosta) z cieniowanego punktu w kierunku œwiat³a
Ray3 ray(A, vectorAB);

Vec3 ignored;

for(int i=0;i<world.objects.size();i++)       
{
// jeœli jakiœ obiekt jest na drodze promienia oraz trafienie
// nast¹pi³o bli¿ej ni¿ odleg³oœæ punktu do œwiat³a,
// obiekt jest w cieniu
if (world.objects[i]->HitTest(ray, currDistance, ignored) && currDistance < distAB)
return true;

}


return false;
}