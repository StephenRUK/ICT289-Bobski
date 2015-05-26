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

	int* indexes;
	int indexCount;

	GLuint textureID;

} Model;

#endif