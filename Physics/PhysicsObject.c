#include "PhysicsObject.h"
#include "../Maths/MathsUtil.h"

void physObjUpdateVelocity(PhysicsObject* physics, float dt) {
	float dv[3];
	mathVector3MultiplyScalar(dt, physics->acceleration, dv);

	mathVector3Add(dv, physics->velocity, physics->velocity);
}
