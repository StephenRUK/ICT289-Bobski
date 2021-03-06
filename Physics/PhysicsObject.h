#ifndef PHYSOBJ_H
#define PHYSOBJ_H

#include "../Includes.h"

/**
* Physics Object
* Method prefix: physObj
**/

/*
* Physics object for attaching to a GameObject.
* Keeps track of relevant physics values.
*/
typedef struct PhysicsObject {
	float mass;				// Mass in kg
	float gravityFactor;	// 0=no gravity, 1=standard gravity, etc.
	int isKinetic;			// false = not affected by physics

	vec3 velocity;			// Directed velocity in m/s^2
	vec3 acceleration;		// Directed acceleration in m/s^2

} PhysicsObject;

void physObjSetDefaults(PhysicsObject* phys);

#endif
