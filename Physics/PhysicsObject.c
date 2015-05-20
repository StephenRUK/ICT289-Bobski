#include "PhysicsObject.h"
#include "../Maths/MathsUtil.h"

PhysicsObject* physObjCreate() {
	PhysicsObject* phys = malloc(sizeof(PhysicsObject));

	phys->acceleration[0] = 0;
	phys->acceleration[1] = 0;
	phys->acceleration[2] = 0;

	phys->velocity[0] = 0;
	phys->velocity[1] = 0;
	phys->velocity[2] = 0;

	phys->isKinetic = true;
	phys->gravityFactor = 1;
	phys->mass = 1;

	return phys;
}