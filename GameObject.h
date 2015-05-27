#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "Transform.h"
#include "Model.h"
#include "Physics/PhysicsObject.h"

typedef struct GameObject {
	Model model;
	Transform transform;
	PhysicsObject physics;

	//GameObject** children;
	//int childrenLength;
} GameObject;

GameObject* gameObjCreate(char* modelPath, char* texturePath);

void gameObjUpdatePhysics(GameObject* obj, float dt);

void gameObjDrawModel(GameObject* obj);

#endif