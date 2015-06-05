#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "Transform.h"
#include "Model.h"
#include "Physics/PhysicsObject.h"
#include "Camera.h"

typedef struct GameObject {
	Model model;
	Transform transform;
	PhysicsObject physics;
	int protag;

	//GameObject** children;
	//int childrenLength;
} GameObject;

GameObject* gameObjCreate(char* modelPath, char* texturePath);

void gameObjUpdatePhysics(GameObject* obj, float dt, Camera cam);

void gameObjDrawModel(GameObject* obj);

#endif