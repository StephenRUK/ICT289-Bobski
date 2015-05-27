#ifndef MODEL_H
#define MODEL_H

#include "Includes.h"

typedef struct Model {
	GLfloat* vertices;
	int vertexCount;

	GLfloat* normals;
	GLfloat* textureCoords;

	GLuint textureID;

} Model;

#endif