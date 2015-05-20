#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "../Types.h"
#include "../GameObject.h"

/**
* Collider: Axis-aligned bounding box (AABB)
* Reference:
*	http://www.euclideanspace.com/threed/animation/collisiondetect/
**/
typedef struct BoundingBox {
	vec3 min;
	vec3 max;
} BoundingBox;

BoundingBox bboxCalculateFromModel(Model* model);
void bboxRotateAndRecalculate(BoundingBox* bbox);

#endif