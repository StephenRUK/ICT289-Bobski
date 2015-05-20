#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Types.h"

typedef struct Transform {
	vec3 position;
	vec3 scale;

	vec3 rotationAngles;

} Transform;

void transformSetDefaults(Transform* tf);

#endif