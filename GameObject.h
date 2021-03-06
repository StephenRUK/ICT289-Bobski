#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "Transform.h"
#include "Model.h"
#include "Physics/PhysicsObject.h"
#include "Physics/BoundingBox.h"

typedef struct GameObject {
	Model model;
	Transform transform;
	PhysicsObject physics;
	BoundingBox bbox;

	//GameObject** children;
	//int childrenLength;
} GameObject;

GameObject* gameObjCreate(char* modelPath, char* texturePath);

void gameObjUpdatePhysics(GameObject* obj, float dt);

void gameObjDrawModel(GameObject* obj);

void gameObjScale(GameObject* obj, float scaleX, float scaleY, float scaleZ);

#endif