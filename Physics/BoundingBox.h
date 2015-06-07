#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "../Types.h"
#include "../Model.h"

/**
* Collider: Axis-aligned bounding box (AABB)
* Reference:
*	http://www.euclideanspace.com/threed/animation/collisiondetect/
**/
typedef struct BoundingBox {
	float minX,minY,minZ;
	float maxX,maxY,maxZ;
	float centreX,centreY,centreZ;
} BoundingBox;

void bboxCalculateFromModel(BoundingBox* bbox, Model* model);
void bboxRotate(BoundingBox* bbox, float angle);
void bboxScale(BoundingBox* bbox, float scaleX, float scaleY, float scaleZ);

#endif