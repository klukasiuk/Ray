#include "framebuffer.h"

#include "SimpleGL.h"


FrameBuffer::FrameBuffer(int x , int y)
{
  width = x;
  height = y;

  pixels = new GLubyte[width * height * 3];

  for(int i=0;i<width*height*3;i++)
  pixels[i]=0;
}

FrameBuffer::~FrameBuffer()
{
  if(pixels != NULL)
  delete[] pixels; 
}

void FrameBuffer::setsize(int x , int y)
{
  width = x;
  height = y;

  if (pixels != NULL)
  delete[] pixels; 

  pixels = NULL;

  pixels = new GLubyte[width * height * 3];

  for(int i=0;i<width*height*3;i++)
  pixels[i]=0;
}

 RGB FrameBuffer::getpixel(int x , int y )
 {
  if(x < 0 || x >= width )
  return RGB(0,0,0);

  if(y < 0 || y >= height)
  return RGB(0,0,0);

  RGB c;

  int a = (x + y*width) * 3;

  c.r = pixels[a + 0];
  c.g = pixels[a + 1];
  c.b = pixels[a + 2];

  return c;
 }

 void FrameBuffer::setpixel(int x , int y , int r , int g , int b)
 {
  if(x < 0 || x >= width )
  return;

  if(y < 0 || y >= height)
  return;

  int a = (y + x*height) * 3;

  pixels[a + 0] = r;
  pixels[a + 1] = g;
  pixels[a + 2] = b;
 }

 void FrameBuffer::setpixel(int x , int y , RGB c)
 {
  if(x < 0 || x >= width )
  return;

  if(y < 0 || y >= height)
  return;

  int a = (x + y*width) * 3;
  pixels[a + 0] = (GLubyte)c.r;
  pixels[a + 1] = (GLubyte)c.g;
  pixels[a + 2] = (GLubyte)c.b;
 }

 void FrameBuffer::blur()
 {
    RGB pix;

	for(int x=0;x<width;x++)
	for(int y=0;y<height;y++)
	{
	  if( x - 1 >= 0)
      if( y - 1 >= 0)
	  if( x + 1 < width)
	  if( y + 1 < height)
	  {
		  pix = getpixel(x,y)* 0.6 + getpixel(x-1,y)*0.1 + getpixel(x,y-1)*0.1 + getpixel(x+1,y)*0.1 + getpixel(x,y+1)*0.1    ;
		  setpixel(x,y,pix);
	  }
	}
 }

 void FrameBuffer::draw()
 {
	 rgb_buffer(0.0f, 0.0f, 1.0f, 1.0f, width, height, (int*)pixels);
 }

 void FrameBuffer::saveBMP(const char * filename)
 {
	 FILE *f;
	 unsigned char *img = NULL;
	 int filesize = 54 + 3 * width*height;

	 img = (unsigned char *)malloc(3 * width*height);
	 memset(img, 0, sizeof(img));

	 for (int x = 0; x<width;  x++)
	 for (int y = 0; y<height; y++)
	 {
		 img[(x + y*width) * 3 + 2] = (unsigned char)pixels[(x + y*width) * 3 + 0];
		 img[(x + y*width) * 3 + 1] = (unsigned char)pixels[(x + y*width) * 3 + 1];
		 img[(x + y*width) * 3 + 0] = (unsigned char)pixels[(x + y*width) * 3 + 2];
	 }

	 unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	 unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	 unsigned char bmppad[3] = { 0,0,0 };

	 bmpfileheader[2] = (unsigned char)(filesize);
	 bmpfileheader[3] = (unsigned char)(filesize >> 8);
	 bmpfileheader[4] = (unsigned char)(filesize >> 16);
	 bmpfileheader[5] = (unsigned char)(filesize >> 24);

	 bmpinfoheader[4] = (unsigned char)(width);
	 bmpinfoheader[5] = (unsigned char)(width >> 8);
	 bmpinfoheader[6] = (unsigned char)(width >> 16);
	 bmpinfoheader[7] = (unsigned char)(width >> 24);
	 bmpinfoheader[8] = (unsigned char)(height);
	 bmpinfoheader[9] = (unsigned char)(height >> 8);
	 bmpinfoheader[10] = (unsigned char)(height >> 16);
	 bmpinfoheader[11] = (unsigned char)(height >> 24);

	 f = fopen("img.bmp", "wb");
	 fwrite(bmpfileheader, 1, 14, f);
	 fwrite(bmpinfoheader, 1, 40, f);

	 for (int i = 0; i<height; i++)
	 {
		 fwrite(img + (width*i * 3), 3, width, f);
		 fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
	 }

	 fclose(f);
 }