#include "Transform.h"

void transformSetDefaults(Transform* tf) {
	tf->position[0] = 0;
	tf->position[1] = 0;
	tf->position[2] = 0;

	tf->scale[0] = 1;
	tf->scale[1] = 1;
	tf->scale[2] = 1;

	tf->rotationAngles[0] = 0;
	tf->rotationAngles[1] = 0;
	tf->rotationAngles[2] = 0;
}
