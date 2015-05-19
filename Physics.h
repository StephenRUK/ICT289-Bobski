#ifndef PHYSICS_H
#define PHYSICS_H

#include "Includes.h"

typedef struct Physics {
	float mass;				// Mass in kg
	float gravityFactor;	// 0=no gravity, 1=standard gravity, etc.

	vec3 velocity;			// Directed velocity in m/s^2
	vec3 acceleration;		// Directed acceleration in m/s^2

} Physics;


#endif
