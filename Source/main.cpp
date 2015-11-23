#include <GLFW/glfw3.h>                                                           // Obs³uga okna
#include <FtglSrc/FTGL/ftgl.h>                                                    // Czcionka
#include <string>

#include "raytracer.h"
#include "framebuffer.h"
#include "logger.h"
#include "timer.h"
#include "error.h"

//#include <vld.h>


using namespace colors;                                                           // Importuje kolory z color.h

GLFWwindow * window;                                                              // Uchwyt okna

int width = 640 ;                                                                 // Wymiary okna
int height = 480 ;

bool run = true;                                                                  // Warunek g³ownej pêtli

FrameBuffer frame(width,height);                                                  // Bufor okna (RGB)

RayTracer * raytracer;                                                            // Raytracer

Camera * cam;                                                                     // Kamera do raytracera

vector<Material*> materials;

bool click;

bool change = true;

double clicked_x;
double clicked_y;                                                       

FPS fps;

Logger logger("log");

const int FPS_block = 60;

FTGLTextureFont font("calibri.ttf");

bool multi = true;

Timer rendertime;

double rtime;


Material * addMaterial( Material * m)
{
 materials.push_back(m);
 return m;
}


void mouse(GLFWwindow * window, int button , int action , int mods)               // Obs³uga myszki
{

	if(button == GLFW_MOUSE_BUTTON_LEFT )
    if(action == GLFW_PRESS )
	{

	}

	if(button == GLFW_MOUSE_BUTTON_RIGHT )
	{
			if(action == GLFW_PRESS )
			{
			double x,y;
			glfwGetCursorPos(window,&x,&y);

			y = height - y;

			click = true;

			clicked_x = x;
			clicked_y = y;
			}



		    if(action == GLFW_RELEASE )
			{
			click = false;
			}
	}
}

void button(GLFWwindow * window, int key, int scancode, int action, int mods)    // Obs³uga klawiatury
{
	 if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
     run = false;

	 if (key == GLFW_KEY_M && action == GLFW_PRESS)
     multi = ! multi; 

	 if (key == GLFW_KEY_B && action == GLFW_PRESS)
     frame.saveBMP("screenshot.bmp");

	 if (key == GLFW_KEY_P && action == GLFW_PRESS)
	 {
     raytracer->draw_depth = !raytracer->draw_depth;
	 change = true;
	 }

	 if (key == GLFW_KEY_U && action == GLFW_PRESS)
	 {
	 Sphere * b = static_cast<Sphere*>(raytracer->world.objects[0]);

	 b->pos.y += 1;
  
	 change = true;
	 }

	 if (key == GLFW_KEY_J && action == GLFW_PRESS)
	 {
	 Sphere * b = static_cast<Sphere*>(raytracer->world.objects[0]);

	 b->pos.y -= 1;
  
	 change = true;
	 }
}

void resize(GLFWwindow * window , int x , int y)
{
	//width = x;
	//height = y;


	//frame.setsize(x,y);
}



void InitGLFW()
{
	glfwSetErrorCallback(error);

	int result = glfwInit();                                                                 // Inicjalizacje GLFW

	int major, minor, rev;

    glfwGetVersion(&major, &minor, &rev);

	logger.msg("OpenGL major :",major);
	logger.msg("OpenGL minor :",minor);
	logger.msg("OpenGL revision :",rev);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

	if(result == GL_FALSE )
	logger<<"Nie zainicjalizowano glfw";
	else
    logger<<"Inicjalizacja glfw";

    window = glfwCreateWindow( width , height , "RayTracer", NULL , NULL );                  // Tworzenie okna

	if(window == NULL)
	logger<<"Nie utworzono okna";
	else
	logger<<"Utworzono okno";

    glfwMakeContextCurrent(window);	                                                         // Wybieram kontekst

	glfwSetMouseButtonCallback(window,mouse);                                                // Ustawiam obs³ugê myszy

	glfwSetKeyCallback(window,button);                                                       // Ustawiam obs³ugê klawiatury

	glfwSetFramebufferSizeCallback(window,resize);
}

// Zmiana rzutowania
 void projection(int x , int y)
{
	glViewport(0,0,x,y);						                                             // Wybieram obszar wyswietlania

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,x,0,y,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		
}

void InitOpenGL()
{
	projection(width,height);                                                                // Ustawiam rzutowanie

	glRasterPos2i(0, 0);                                                                     // Pozycja rasteryzacji
	
	glDisable(GL_ALPHA_TEST);                                                                // Wy³¹czenie zbêdnych g³upot
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_DITHER);
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_LOGIC_OP);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);
    glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
    glPixelTransferi(GL_RED_SCALE, 1);
    glPixelTransferi(GL_RED_BIAS, 0);
    glPixelTransferi(GL_GREEN_SCALE, 1);
    glPixelTransferi(GL_GREEN_BIAS, 0);
    glPixelTransferi(GL_BLUE_SCALE, 1);
    glPixelTransferi(GL_BLUE_BIAS, 0);
    glPixelTransferi(GL_ALPHA_SCALE, 1);
    glPixelTransferi(GL_ALPHA_BIAS, 0);
}

void InitRaytracer()
{
	World world(Sky);



	Material * RedMatte = addMaterial(new PerfectDiffuse(Red));
	Material * BlueMatte = addMaterial(new PerfectDiffuse(Blue));
	Material * GreenMatte = addMaterial(new PerfectDiffuse(Green));

	Material * GreyMatte = addMaterial(new PerfectDiffuse(DarkGrey));



	Material * RedPhong = addMaterial(new Phong(Red, 0.8 , 1 , 30));
	Material * BluePhong = addMaterial(new Phong(Green, 0.8 ,1 , 30));
	Material * GreenPhong = addMaterial(new Phong(Blue, 0.8 ,1 , 30));

	Material * GreyPhong = addMaterial(new Phong(DarkGrey, 0.8 ,1 , 30));



	Material * RedRef = addMaterial(new Reflective(LightRed, 0.4, 1, 300, 0.6));
	Material * BlueRef = addMaterial(new Reflective(LightGreen, 0.4, 1, 300, 0.6));
	Material * GreenRef = addMaterial(new Reflective(LightBlue, 0.4, 1, 300, 0.6));

	Material * GreyRef = addMaterial(new Reflective(DarkGrey, 0.4, 1, 300, 0.6));


	Material * Mirror = addMaterial(new Reflective(White, 0.0 , 0, 0, 1.0));


	world.AddObject(new Sphere(Vec3(-5, 0, 0), 2 , RedPhong));
	world.AddObject(new Sphere(Vec3( 0, 0, 0), 2 , BluePhong));
	world.AddObject(new Sphere(Vec3( 5, 0, 0), 2 , GreenPhong));

	world.AddObject(new Sphere(Vec3(-5, 0, 10), 2 , RedRef));
	world.AddObject(new Sphere(Vec3( 0, 0, 10), 2 , BlueRef));
	world.AddObject(new Sphere(Vec3( 5, 0, 10), 2 , Mirror));

	world.AddObject(new Plane(Vec3( 0, -2, 2.5), Vec3(0,1,0) , GreyMatte));

	
	world.AddLight(PointLight(Vec3(0, 3000, -3000), White));


	cam = new Persp(8 , 6 , 8, Vec3(0,0,-10),Vec3(0,0,5),Vec3(0,1,0) );


	raytracer = new RayTracer(cam , world , &frame);
}

 // Inicjalizcja
 void init()
{
   InitGLFW();                             // Inicjalizuje GLFW

   InitOpenGL();                           // Inicjalizuje OpenGL
		
   InitRaytracer();                        // Inicjalizuje Raytracing

   fps.Block(0);

   fps.Set_Frames(1000);

   font.FaceSize(16);

   font.UseDisplayList(true);
}


 // Rysowanie klatki
 void draw()
 {
	frame.draw();                          // Rysuje piksele na ekranie

	string fpst = "FPS : ";
	fpst += std::to_string(fps.rate);

	string fra = " Draw time : ";
	fra += std::to_string(rtime);

	fra += " ms";

	glPushMatrix();

	glLoadIdentity();

	//font.Render(fpst.data());

	glTranslated(0,18,0);

	font.Render(fra.data());

	glPopMatrix();
    
    glfwSwapBuffers(window);               // Zamieniam bufory
 }


 // Obs³uga wejœcia
 void input()
 {
	if(glfwGetKey(window , GLFW_KEY_W) == GLFW_PRESS)
	{
	cam->pos = cam->pos + cam->dir;
	change = true;
	}

	if(glfwGetKey(window , GLFW_KEY_S) == GLFW_PRESS)
	{
	cam->pos = cam->pos - cam->dir;
	change = true;
	}

	if(glfwGetKey(window , GLFW_KEY_A) == GLFW_PRESS)
	{
	cam->pos = cam->pos - cam->right;
	change = true;
	}

	if(glfwGetKey(window , GLFW_KEY_D) == GLFW_PRESS)
	{
	cam->pos = cam->pos + cam->right;
	change = true;
	}

	if(glfwGetKey(window , GLFW_KEY_SPACE) == GLFW_PRESS)
	{
	cam->pos = cam->pos + Vec3(0,1,0)*0.4;
	change = true;
	}

	if(glfwGetKey(window , GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
	cam->pos = cam->pos - Vec3(0,1,0)*0.4;
	change = true;
	}



    glfwPollEvents();                      // Obs³uguje eventy



	GLenum glError;                        // Sprawdzam b³edy OGL

    glError = glGetError();

    if (glError != GL_NO_ERROR)
	error(glError , "Blad OpenGL");
 }



 // Aktualizacja
 void update()
 {

	 Sphere * b = static_cast<Sphere*>(raytracer->world.objects[0]);

	 b->pos.y = 2.5 + 2.5*sin(glfwGetTime());
	 b->pos.z = 10 * cos(glfwGetTime());
  
	 change = true;




	 if( 1)
	 {
	  rendertime.Start();


	  if(multi)
	 raytracer->MultiTrace();                   // Raytracing
	  else
	 raytracer->Trace();



	  rendertime.Update();

	  rtime = rendertime.GetTime();

	  rendertime.Reset();



	 frame.blur();
	 change = false;
	 }

	if(click)                              // Rotacja kamery
	{
	  double x,y;
	  glfwGetCursorPos(window,&x,&y);

	  y = height - y;

	  double dx = x - clicked_x;
	  double dy = y - clicked_y;

	  if( dy != 0 )
	  {
	  cam->rotateX( -dy/50.0 );
	  change = true;
	  }

	  if( dx != 0)
	  {
	  cam->rotateY( -dx/100.0 );
	  change = true;
	  }


	  clicked_x = x;
	  clicked_y = y;
	}
 }


 // Zwolnienie zasobów
 void release()
 {
   delete raytracer;
   delete cam;

   for(int i=0;i<materials.size();i++)
   delete materials[i];

   glfwDestroyWindow(window);
   glfwTerminate();
 }


int main()
{
	init();

	while(run && !glfwWindowShouldClose(window))
	{
	  draw();

	  input();

	  update();

	  fps.Update();
	}
	
    release();

	return 0;
}