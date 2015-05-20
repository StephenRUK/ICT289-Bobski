#include "GameObject.h"

void gameObjUpdatePhysics(GameObject* obj, float dt) {
	Transform* transform = &(obj->transform);
	PhysicsObject* phys = &(obj->physics);


	// 1 - Update position
	vec3 deltaPos;
	mathVector3MultiplyScalar(dt, phys->velocity, deltaPos);
	mathVector3Add(deltaPos, transform->position, transform->position);

	// 2 - Update velocity
	physObjUpdateVelocity(phys, dt);

}