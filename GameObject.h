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

	vec3 rotationAngles;

} Transform;

typedef struct GameObject {
	Model model;
	Transform transform;
	PhysicsObject physics;

	//GameObject** children;
	//int childrenLength;
} GameObject;

void gameObjApplyDefaultTransform(GameObject* obj);

void gameObjUpdatePhysics(GameObject* obj, float dt);

void gameObjDrawModel(GameObject* obj);

#endif