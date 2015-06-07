#include "CollisionResolution.h"

int cResCheckCollision(BoundingBox* bbox1, BoundingBox* bbox2) {
	// Return true/false, or intersection?

	if ((bbox1->minX < bbox2->maxX && bbox1->maxX > bbox2->minX)
		&& (bbox1->minY < bbox2->maxY && bbox1->maxY > bbox2->minY)
		&& (bbox1->minZ < bbox2->maxZ && bbox1->maxZ > bbox2->minZ)){

		return 1;
	}

	return 0;
}

void cResResolveCollision(GameObject* a, GameObject* b) {
	
	// Collisions are buggy.
	
}