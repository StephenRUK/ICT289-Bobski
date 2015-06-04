#include "BoundingBox.h"
#include "../Maths/MathsUtil.h"

/*
* bboxCalculateFromModel
*
* Calculates the bounding box from the model's vertices.
* Doesn't incorporate scaling after loading the model.
* Must be updated after scaling operations. (i.e. write a function to apply scaling to transform and bbox)
*/
BoundingBox bboxCalculateFromModel(Model* model) {
	BoundingBox bbox;
	vec3* verts = model->vertices;
	
	int i;
	for (i = 0; i < model->vertexCount; i++) {
		
		if (verts[i][0] < bbox.min[0]) bbox.min[0] = verts[i][0];	// min x
		if (verts[i][0] > bbox.max[0]) bbox.max[0] = verts[i][0];	// max x
		if (verts[i][1] < bbox.min[1]) bbox.min[1] = verts[i][1];	// min y
		if (verts[i][1] > bbox.max[1]) bbox.max[1] = verts[i][1];	// max y
		if (verts[i][2] < bbox.min[2]) bbox.min[2] = verts[i][2];	// min z
		if (verts[i][2] > bbox.max[2]) bbox.max[2] = verts[i][2];	// max z
	}

	// Calculate centre point (max-min)/2
	mathVector3Subtract(bbox.max, bbox.min, bbox.centre);
	mathVector3MultiplyScalar(0.5, bbox.centre, bbox.centre);

	return bbox;
}
