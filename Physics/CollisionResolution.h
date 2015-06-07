#ifndef COLLISIONRESOLUTION_H
#define COLLISIONRESOLUTION_H

#include "../Types.h"
#include "../GameObject.h"
#include "BoundingBox.h"

int cResCheckCollision(BoundingBox* bbox1, BoundingBox* bbox2);
void cResResolveCollision(GameObject* a, GameObject* b);

#endif