#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "GL/freeglut.h"

typedef struct Bitmap {
	unsigned int width;
	unsigned int height;
	unsigned int dataBytes;
	unsigned char* data;
} Bitmap;

void imgLoadBitmap(char* filename, Bitmap* target);
GLuint imgLoadBitmapToTexture(char* filename);
GLuint imgLoadBitmapToSkybox(char* filename);

#endif