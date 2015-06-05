#include "Includes.h"
#include "Move.h"
#include <math.h>

#include <stdio.h>

/*
* Spongebob movement implementation
*
* Angles:
*	Left is -, right is +
*	Up is +, down is -
*
* Reference: Unit sphere & circle, unit sphere to cartesian coordinates
*
*/

Move movWithDefaults() {
	Move mov;

	mov.X = 0;
	mov.Y = 1;
	mov.Z = -1;

	mov.fwdX = 0;
	mov.fwdY = 0;
	mov.fwdZ = -1;

	mov.upX = 0;
	mov.upY = 1;
	mov.upZ = 0;

	mov.pitch = 0;
	mov.yaw = 0;

	mov.maxPitch = mathDegToRad(85);

	return mov;
}

void movWalkForwards(Move* mov, GLfloat distance) {
	mov->X += mov->fwdX * distance;
	mov->Z += mov->fwdZ * distance;
}

void movWalkBackwards(Move* mov, GLfloat distance) {
	movWalkForwards(mov, -distance);
}

void movStrafeLeft(Move* mov, GLfloat distance) {
	vec3 up = { mov->upX, mov->upY, mov->upZ };
	vec3 dir = { mov->fwdX, mov->fwdY, mov->fwdZ };
	vec3 left;
	mathCrossProduct(up, dir, left);

	mov->X += distance * left[0];
	mov->Z += distance * left[2];
}

void movStrafeRight(Move* mov, GLfloat distance) {
	vec3 up = { mov->upX, mov->upY, mov->upZ };
	vec3 dir = { mov->fwdX, mov->fwdY, mov->fwdZ };
	vec3 right;
	mathCrossProduct(dir, up, right);

	mov->X += distance * right[0];
	mov->Z += distance * right[2];
}


void movLookUp(Move* mov, GLfloat deltaAngle) {
	mov->pitch = min(mov->pitch + deltaAngle, mov->maxPitch);

	mov->fwdY = sin(mov->pitch);
	mov->fwdZ = -1 * cos(mov->pitch)*cos(mov->yaw);
}

void movLookDown(Move* mov, GLfloat deltaAngle) {
	mov->pitch = max(mov->pitch - deltaAngle, -1 * mov->maxPitch);

	mov->fwdY = sin(mov->pitch);
	mov->fwdZ = -1 * cos(mov->pitch)*cos(mov->yaw);
}

void movLookLeft(Move* mov, GLfloat deltaAngle) {
	mov->yaw -= deltaAngle;
	if (mov->yaw < -mathDegToRad(360)) mov->yaw += mathDegToRad(360);

	mov->fwdX = cos(mov->pitch) * sin(mov->yaw);
	mov->fwdZ = -1 * cos(mov->pitch) * cos(mov->yaw);
}

void movLookRight(Move* mov, GLfloat deltaAngle) {
	mov->yaw += deltaAngle;
	if (mov->yaw > mathDegToRad(360)) mov->yaw -= mathDegToRad(360);

	mov->fwdX = cos(mov->pitch) * sin(mov->yaw);
	mov->fwdZ = -1 * cos(mov->pitch) * cos(mov->yaw);
}