#include "PhysicsObject.h"
#include "../Maths/MathsUtil.h"

void physObjSetDefaults(PhysicsObject* phys) {
	phys->acceleration[0] = 0;
	phys->acceleration[1] = 0;
	phys->acceleration[2] = 0;

	phys->velocity[0] = 0;
	phys->velocity[1] = 0;
	phys->velocity[2] = 0;

	phys->gravityFactor = 1;
	phys->mass = 1;
}

void physObjUpdateVelocity(PhysicsObject* physics, float dt) {
	float dv[3];
	mathVector3MultiplyScalar(dt, physics->acceleration, dv);

	mathVector3Add(dv, physics->velocity, physics->velocity);
}
