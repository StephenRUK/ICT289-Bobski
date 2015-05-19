#include "ImageLoader.h"
#include "GL/freeglut.h"
#include <stdio.h>

void imgLoadBitmap(char* filename, Bitmap* target) {
	unsigned char header[54];
	unsigned int width, height;
	unsigned int imageSize;

	unsigned char* data;
	FILE* file;
	fopen_s(&file, filename, "rb");
	if (!file) return NULL;

	fread(header, 1, 54, file);

	// Typecasting pointers required to get uint from byte array.
	imageSize = *(unsigned int*)(&header[0x22]);
	width = *(unsigned int*)(&header[0x12]);
	height = *(unsigned int*)(&header[0x16]);

	if (imageSize == 0) {
		imageSize = width*height * 3;	// Assume 24-bit depth if image size missing
	}

	//
	// Read pixel data byte-wise
	//
	data = malloc(imageSize * sizeof(unsigned char));
	fread(data, sizeof(unsigned char), imageSize, file);
	fclose(file);

	target->width = width;
	target->height = height;
	target->dataBytes = imageSize;
	target->data = data;
}

/*
*	Loads a bitmap file into memory and assigns it a texture ID in OpenGL.
*/
GLuint imgLoadBitmapToTexture(char* filename) {
	Bitmap tex;
	imgLoadBitmap(filename, &tex);

	//
	// Load data into OpenGL texture
	// Set our default parameters for textures.
	// Texture parameters can be modified later by binding again.
	//
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tex.data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}