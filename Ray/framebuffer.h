#pragma once
#include <GLFW\glfw3.h>

#include "color.h"
#include <stddef.h>
#include <stdio.h>              // FILE
#include <stdlib.h>             // malloc
#include <string.h>



class FrameBuffer
{
 public:

	GLubyte * pixels;

	int width;
	int height;

	FrameBuffer(int x , int y);
   ~FrameBuffer();

	void setsize(int x , int y);

	RGB  getpixel(int x , int y);

	void setpixel(int x , int y , int r , int g , int b);
	void setpixel(int x , int y , RGB c);

	void blur();

	void draw();

	void saveBMP(const char * file);
};