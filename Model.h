#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"

typedef struct Model {
	GLfloat* vertices;
	int verticesLength;

	GLfloat* normals;
	int normalsLength;

	GLuint textureID;
	GLfloat* textureCoords;
	int textureCoordsLength;
} Model;

#endif