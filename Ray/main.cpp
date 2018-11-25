#include "SimpleGL.h"
#include "raytracer.h"
#include "framebuffer.h"
#include "logger.h"
#include "timer.h"
#include "error.h"


using namespace colors;

const int window_width = 1200;													// Window dimmensions
const int window_height = 800;

const int framebuffer_width = 800;												// Raytracer framebuffer size
const int framebuffer_height = 600;

bool run;

RayTracer * raytracer;

Camera * cam;

FrameBuffer frameBuffer(framebuffer_width, framebuffer_height);

vector<Material*> materials;

FPS fps;

Logger logger("log");

Timer rendertime;

bool mouse_pressed = false;
int  mouse_last_x = 0;
int  mouse_last_y = 0;


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
	{
		mouse_pressed = true;

		getMousePosition(mouse_last_x, mouse_last_y);
	}

	if (button == Mouse_Left && action == Released)
	{
		mouse_pressed = false;
	}
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
	Material * BluePhong = addMaterial(new Phong(Blue, 0.8, 1, 30));
	Material * GreenPhong = addMaterial(new Phong(Green, 0.8, 1, 30));
	Material * GreyPhong = addMaterial(new Phong(DarkGrey, 0.8, 1, 30));

	Material * RedRef = addMaterial(new Reflective(LightRed, 0.4, 1, 300, 0.6));
	Material * BlueRef = addMaterial(new Reflective(LightBlue, 0.4, 1, 300, 0.6));
	Material * GreenRef = addMaterial(new Reflective(LightGreen, 0.4, 1, 300, 0.6));
	Material * GreyRef = addMaterial(new Reflective(DarkGrey, 0.4, 1, 300, 0.6));

	Material * Mirror = addMaterial(new Reflective(White, 0.1, 0.1, 0, 0.9));

	world.AddObject(new Sphere(Vec3(-5, 0, 0), 2, RedMatte));
	world.AddObject(new Sphere(Vec3(0, 0, 0), 2, BlueMatte));
	world.AddObject(new Sphere(Vec3(5, 0, 0), 2, GreenMatte));

	world.AddObject(new Sphere(Vec3(-5, 0, 5), 2, RedPhong));
	world.AddObject(new Sphere(Vec3(0, 0, 5), 2, BluePhong));
	world.AddObject(new Sphere(Vec3(5, 0, 5), 2, GreenPhong));

	world.AddObject(new Sphere(Vec3(-5, 0, 10), 2, RedRef));
	world.AddObject(new Sphere(Vec3(0, 0, 10), 2, BlueRef));
	world.AddObject(new Sphere(Vec3(5, 0, 10), 2, Mirror));

	world.AddObject(new Plane(Vec3(0, -2, 2.5), Vec3(0, 1, 0), GreyMatte));

	world.AddLight(PointLight(Vec3(0, 3000, -3000), White));

	cam = new Persp(8, 6, 8, Vec3(0, 0, -10), Vec3(0, 0, 5), Vec3(0, 1, 0));

	raytracer = new RayTracer(cam, world, &frameBuffer);
}

void InitRaytracer2()
{
	World world(Sky);


	Material * RedRef = addMaterial(new Reflective(LightRed, 0.4, 1, 300, 0.6));
	Material * BlueRef = addMaterial(new Reflective(LightBlue, 0.4, 1, 300, 0.6));
	Material * GreenRef = addMaterial(new Reflective(LightGreen, 0.4, 1, 300, 0.6));
	Material * GreyRef = addMaterial(new Reflective(LightGrey, 0.4, 1, 300, 0.6));


	world.AddObject(new Sphere(Vec3(-5, 0, 5), 2, RedRef));
	world.AddObject(new Sphere(Vec3(0, 0, 10), 2, BlueRef));
	world.AddObject(new Sphere(Vec3(5, 0, 5), 2, GreenRef));

	world.AddObject(new Plane(Vec3(0, -2, 2.5), Vec3(0, 1, 0), GreyRef));

	world.AddLight(PointLight(Vec3(0, 10, 0), White));

	cam = new Persp(8, 6, 8, Vec3(0, 2, -15), Vec3(0, 0, 5), Vec3(0, 1, 0));

	raytracer = new RayTracer(cam, world, &frameBuffer);
}

void camera_rotation_handler()
{
	if (!mouse_pressed)
		return;

	int mouse_x;
	int mouse_y;

	getMousePosition(mouse_x, mouse_y);

	int dx = mouse_x - mouse_last_x;
	int dy = mouse_y - mouse_last_y;

	if (dy != 0)
	{
		cam->rotateX(dy / 100.0);
	}

	if (dx != 0)
	{
		cam->rotateY(-dx / 100.0);
	}


	mouse_last_x = mouse_x;
	mouse_last_y = mouse_y;
}

void camera_movement_handler()
{
	if( getKeyState(Key_W) == Pressed)
		cam->pos = cam->pos + cam->dir;
			
	if (getKeyState(Key_S) == Pressed)
		cam->pos = cam->pos - cam->dir;

	if (getKeyState(Key_A) == Pressed)
		cam->pos = cam->pos - cam->right;

	if (getKeyState(Key_D) == Pressed)
		cam->pos = cam->pos + cam->right;

	if (getKeyState(Key_Space) == Pressed)
		cam->pos = cam->pos + Vec3(0, 1, 0)*0.4;

	if (getKeyState(Key_Control) == Pressed)
		cam->pos = cam->pos - Vec3(0, 1, 0)*0.4;
}

void init()
{
	setDoubleBuffered(true);

	initGL(window_width, window_height);

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

	camera_rotation_handler();

	camera_movement_handler();
}

void update()
{
	raytracer->MultiTrace();
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