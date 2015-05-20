#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "Physics/PhysicsObject.h"

typedef struct Model {
	GLfloat* vertices;
	GLfloat* normals;
	int vertexCount;

	GLuint textureID;
	GLfloat* textureCoords;
} Model;

typedef struct Transform {
	vec3 position;
	vec3 scale;

	vec3 rotX, rotY, rotZ;

} Transform;

typedef struct GameObject {
	Model model;
	Transform transform;
	PhysicsObject physics;

	//GameObject** children;
	//int childrenLength;
} GameObject;


void gameObjUpdatePhysics(GameObject* obj);

void gameObjDrawModel(GameObject* obj);

#endif