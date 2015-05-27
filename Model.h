#ifndef MODEL_H
#define MODEL_H

#include "Includes.h"

typedef struct Model {
	vertex3* vertices;
	int vertexCount;

	vertex3* normals;
	vertex2* textureCoords;

	GLuint textureID;

} Model;

#endif