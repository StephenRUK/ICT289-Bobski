#ifndef MODEL_H
#define MODEL_H

#include "Includes.h"

typedef struct Model {
	GLfloat* vertices;
	int vertexCount;

	GLfloat* normals;
	int normalCount;

	GLfloat* textureCoords;
	int texCoordCount;

	int* indices;
	int indexCount;

	GLuint textureID;

} Model;

#endif