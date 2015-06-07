#include "Includes.h"
#include "Camera.h"
#include <math.h>

#include <stdio.h>

/*
* FPS-style camera implementation.
*
* Angles:
*	Left is -, right is +
*	Up is +, down is -
*
* Reference: Unit sphere & circle, unit sphere to cartesian coordinates
*
*/

Camera camWithDefaults() {
	Camera cam;

	// Set up player GameObject. Used for position and collisions.
	cam.player = gameObjCreate("", "");
	cam.player->physics.gravityFactor = 0.0f;
	cam.player->physics.isKinetic = 0;

	// Camera position points to transform position
	cam.X = &(cam.player->transform.position[0]);
	cam.Y = &(cam.player->transform.position[1]);
	cam.Z = &(cam.player->transform.position[2]);

	// Set initial position
	*(cam.X) = 0.0;
	*(cam.Y) = 1.7f;
	*(cam.Z) = 0.0f;

	cam.fwdX = 0;
	cam.fwdY = 0;
	cam.fwdZ = -1;

	cam.upX = 0;
	cam.upY = 1;
	cam.upZ = 0;

	cam.pitch = 0;
	cam.yaw = 0;

	cam.maxPitch = mathDegToRad(85);

	return cam;
}

void camWalkForwards(Camera* cam, GLfloat distance) {
	*(cam->X) += cam->fwdX * distance;
	*(cam->Z) += cam->fwdZ * distance;
}

void camWalkBackwards(Camera* cam, GLfloat distance) {
	camWalkForwards(cam, -distance);
}

void camStrafeLeft(Camera* cam, GLfloat distance) {
	vec3 up = { cam->upX, cam->upY, cam->upZ };
	vec3 dir = { cam->fwdX, cam->fwdY, cam->fwdZ };
	vec3 left;
	mathCrossProduct(up, dir, left);

	*(cam->X) += distance * left[0];
	*(cam->Z) += distance * left[2];
}

void camStrafeRight(Camera* cam, GLfloat distance) {
	vec3 up = { cam->upX, cam->upY, cam->upZ };
	vec3 dir = { cam->fwdX, cam->fwdY, cam->fwdZ };
	vec3 right;
	mathCrossProduct(dir, up, right);

	*(cam->X) += distance * right[0];
	*(cam->Z) += distance * right[2];
}


void camLookUp(Camera* cam, GLfloat deltaAngle) {
	cam->pitch = min(cam->pitch + deltaAngle, cam->maxPitch);

	cam->fwdY = sin(cam->pitch);
	cam->fwdZ = -1*cos(cam->pitch)*cos(cam->yaw);
}

void camLookDown(Camera* cam, GLfloat deltaAngle) {
	cam->pitch = max(cam->pitch - deltaAngle, -1*cam->maxPitch);

	cam->fwdY = sin(cam->pitch);
	cam->fwdZ = -1 * cos(cam->pitch)*cos(cam->yaw);
}

void camLookLeft(Camera* cam, GLfloat deltaAngle) {
	cam->yaw -= deltaAngle;
	if (cam->yaw < -mathDegToRad(360)) cam->yaw += mathDegToRad(360);

	cam->fwdX = cos(cam->pitch) * sin(cam->yaw);
	cam->fwdZ = -1*cos(cam->pitch) * cos(cam->yaw);
}

void camLookRight(Camera* cam, GLfloat deltaAngle) {
	cam->yaw += deltaAngle;
	if (cam->yaw > mathDegToRad(360)) cam->yaw -= mathDegToRad(360);

	cam->fwdX = cos(cam->pitch) * sin(cam->yaw);
	cam->fwdZ = -1 * cos(cam->pitch) * cos(cam->yaw);
}