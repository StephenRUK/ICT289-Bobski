#include "CollisionResolution.h"

int cResCheckCollision(BoundingBox* bbox1, BoundingBox* bbox2) {
	// Return true/false, or intersection?

	if ((bbox1->minX <= bbox2->maxX && bbox1->maxX >= bbox2->minX)
		|| (bbox1->minX <= bbox1->maxY && bbox1->maxY >= bbox2->minX)
		|| (bbox1->minZ <= bbox1->maxZ && bbox1->maxZ >= bbox2->minZ)){

		return 1;

	}

	return 0;

}

void cResResolveCollision(GameObject* a, GameObject* b) {

	//a->physics.velocity[1] = 10;
	//b->physics.velocity[1] = 10;

}