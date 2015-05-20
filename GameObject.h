#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "Physics/PhysicsObject.h"

typedef struct Model {
	GLfloat* vertices;
	int verticesLength;

	GLfloat* normals;
	int normalsLength;

	GLuint textureID;
	GLfloat* textureCoords;
	int textureCoordsLength;
} Model;

typedef struct Transform {
	GLbyte posX, posY, posZ;
	GLbyte scaleX, scaleY, scaleZ;

	GLbyte rotX, rotY, rotZ;
	GLbyte rotAngle;

} Transform;

typedef struct GameObject {
	Model model;
	Transform transform;
	PhysicsObject physics;

	//GameObject** children;
	//int childrenLength;
} GameObject;


void gameObjUpdatePhysics(GameObject* obj);

#endif