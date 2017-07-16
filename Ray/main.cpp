#include "SimpleGL.h"
#include "raytracer.h"
#include "framebuffer.h"
#include "logger.h"
#include "timer.h"
#include "error.h"


using namespace colors;


const int window_width = 800;													// Window dimmensions
const int window_height = 600;


bool run;

RayTracer * raytracer;

Camera * cam;

FrameBuffer frameBuffer(640, 480);

vector<Material*> materials;

FPS fps;

Logger logger("log");

Timer rendertime;

int abc = 0;


void myKeyboardCallback(KeyboardKey key, InputAction action)
{
	if (key == Key_Escape && action == Pressed)
		run = false;

	if (key == Key_B && action == Pressed)
		frameBuffer.saveBMP("screenshot.bmp");
}

void myMouseCallback(int x, int y, MouseButton button, InputAction action)
{
	if (button == Mouse_Left && action == Pressed)
		;

	if (button == Mouse_Right && action == Pressed)
		;
}


Material * addMaterial(Material * m)
{
	materials.push_back(m);
	return m;
}

void InitRaytracer()
{
	World world(Sky);



	Material * RedMatte = addMaterial(new PerfectDiffuse(Red));
	Material * BlueMatte = addMaterial(new PerfectDiffuse(Blue));
	Material * GreenMatte = addMaterial(new PerfectDiffuse(Green));

	Material * GreyMatte = addMaterial(new PerfectDiffuse(DarkGrey));



	Material * RedPhong = addMaterial(new Phong(Red, 0.8, 1, 30));
	Material * BluePhong = addMaterial(new Phong(Green, 0.8, 1, 30));
	Material * GreenPhong = addMaterial(new Phong(Blue, 0.8, 1, 30));

	Material * GreyPhong = addMaterial(new Phong(DarkGrey, 0.8, 1, 30));



	Material * RedRef = addMaterial(new Reflective(LightRed, 0.4, 1, 300, 0.6));
	Material * BlueRef = addMaterial(new Reflective(LightGreen, 0.4, 1, 300, 0.6));
	Material * GreenRef = addMaterial(new Reflective(LightBlue, 0.4, 1, 300, 0.6));

	Material * GreyRef = addMaterial(new Reflective(DarkGrey, 0.4, 1, 300, 0.6));


	Material * Mirror = addMaterial(new Reflective(White, 0.1, 0.1, 0, 0.9));


	world.AddObject(new Sphere(Vec3(-5, 0, 0), 2, RedPhong));
	world.AddObject(new Sphere(Vec3(0, 0, 0), 2, BluePhong));
	world.AddObject(new Sphere(Vec3(5, 0, 0), 2, GreenPhong));

	world.AddObject(new Sphere(Vec3(-5, 0, 10), 2, RedRef));
	world.AddObject(new Sphere(Vec3(0, 0, 10), 2, BlueRef));
	world.AddObject(new Sphere(Vec3(5, 0, 10), 2, Mirror));

	world.AddObject(new Plane(Vec3(0, -2, 2.5), Vec3(0, 1, 0), GreyMatte));


	world.AddLight(PointLight(Vec3(0, 3000, -3000), White));


	cam = new Persp(8, 6, 8, Vec3(0, 0, -10), Vec3(0, 0, 5), Vec3(0, 1, 0));


	raytracer = new RayTracer(cam, world, &frameBuffer);
}


void init()
{
	setDoubleBuffered(true);

	initGL(640, 480);

	view(0.0, 1.0, 1.0, 0.0);

	setKeyboardCallback(myKeyboardCallback);
	setMouseCallback(myMouseCallback);


	InitRaytracer();


	run = true;
}

void release()
{
	delete raytracer;
	delete cam;

	for (int i = 0; i<materials.size(); i++)
	delete materials[i];

	end();
}

void input()
{
	checkEvents();
}

void update()
{
	raytracer->MultiTrace();

	sleep(33);
}

void draw()
{
	frameBuffer.draw();

	swap();
}

int main()
{
	init();

	while(run)
	{
		input();

		update();

		draw();
	}

	release();
}