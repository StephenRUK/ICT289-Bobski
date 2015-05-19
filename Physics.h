#ifndef PHYSICS_H
#define PHYSICS_H

#include "Includes.h"

/*
* Physics object for attaching to a GameObject.
* Keeps track of relevant physics values.
*/
typedef struct Physics {
	float mass;				// Mass in kg
	float gravityFactor;	// 0=no gravity, 1=standard gravity, etc.

	vec3 velocity;			// Directed velocity in m/s^2
	vec3 acceleration;		// Directed acceleration in m/s^2

} Physics;

void physicsApplyGravity(Physics* physics);
void physicsApplyForce(Physics* physics, vec3 force);
bool physicsCheckForCollision(Physics* a, Physics[] others, int othersLength);
void physicsResolveCollision(Physics* a, Physics* b);

#endif
