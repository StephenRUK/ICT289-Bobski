#ifndef COLLIDER_H
#define COLLIDER_H

#include "../Types.h"

/**
* Collider: Axis-aligned bounding box (AABB)
* Reference:
*	http://www.euclideanspace.com/threed/animation/collisiondetect/
**/
typedef struct Collider {
	vec3 min;
	vec3 max;
} Collider;

void colliderRecalculateAABB(Collider* collider, vertex3** vertices);

#endif