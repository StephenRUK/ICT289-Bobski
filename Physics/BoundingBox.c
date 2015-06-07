#include "BoundingBox.h"
#include "../Maths/MathsUtil.h"
#include <math.h>

/*
* bboxCalculateFromModel
*
* Calculates the bounding box from the model's vertices.
* Doesn't incorporate scaling after loading the model.
* Must be updated after scaling operations. (i.e. write a function to apply scaling to transform and bbox)
*/
void bboxCalculateFromModel(BoundingBox* bbox, Model* model) {
	vec3* verts = model->vertices;
	
	int i;
	for (i = 0; i < model->vertexCount; i++) {
		
		if (verts[i][0] < bbox->minX) bbox->minX = verts[i][0];	// min x
		if (verts[i][0] > bbox->maxX) bbox->maxX = verts[i][0];	// max x
		if (verts[i][1] < bbox->minY) bbox->minY = verts[i][1];	// min y
		if (verts[i][1] > bbox->maxY) bbox->maxY = verts[i][1];	// max y
		if (verts[i][2] < bbox->minZ) bbox->minZ = verts[i][2];	// min z
		if (verts[i][2] > bbox->maxZ) bbox->maxZ = verts[i][2];	// max z
	}

	// Calculate centre point (max-min)/2
	bbox->centreX = (bbox->maxX - bbox->minX) / 2;
	bbox->centreY = (bbox->maxY - bbox->minY) / 2;
	bbox->centreZ = (bbox->maxZ - bbox->minZ) / 2;

}

/*
* bboxRotateAndRecalculate
*
* Rotates the bounding box. Used to re-align it with its GameObject after rotation.
* 
*/
void bboxRotate(BoundingBox* bbox, float angle) {
	// Rotation is only around Y axis, as we're dealing with axis-aligned bounding boxes.
	// Affected dimensions are therefore X and Z only.

	float angleInRad = mathDegToRad(angle);

	bbox->centreX = bbox->centreX * sin(angleInRad);
	bbox->centreZ = bbox->centreZ * cos(angleInRad);
	
	bbox->minX = bbox->minX * sin(angleInRad);
	bbox->minZ = bbox->minZ * cos(angleInRad);

	bbox->maxX = bbox->maxX * sin(angleInRad);
	bbox->maxZ = bbox->maxZ * cos(angleInRad);

	//
	// Recalculate bounding box so it's axis-aligned
	//

	// Take min and max of the bounding box?
	// Conditions: http://www.euclideanspace.com/threed/animation/collisiondetect/
}
