#ifndef COLLIDER_H
#define COLLIDER_H

#include "../Types.h"

/**
* Collider: Axis-aligned bounding box (AABB)
**/
typedef struct Collider {
	vec3 min;
	vec3 max;
} Collider;

void colliderRecalculateAABB(Collider* collider, vertex3** vertices);

#endif