#include "GameObject.h"

void gameObjUpdatePhysics(GameObject* obj, float dt) {
	PhysicsObject* phys = &(obj->physics);
	physObjUpdateVelocity(phys, dt);
}