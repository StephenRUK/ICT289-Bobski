#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"
#include "GameObject.h"

typedef struct Camera {
	GameObject* player;

	GLfloat *X, *Y, *Z;
	GLfloat fwdX, fwdY, fwdZ;
	GLfloat upX, upY, upZ;

	GLfloat yaw, pitch;
	GLfloat maxPitch;

} Camera;

Camera camWithDefaults();
void camReset(Camera* cam);

void camWalkForwards(Camera* cam, GLfloat distance);
void camWalkBackwards(Camera* cam, GLfloat distance);
void camStrafeLeft(Camera* cam, GLfloat distance);
void camStrafeRight(Camera* cam, GLfloat distance);

void camLookUp(Camera* cam, GLfloat deltaAngle);
void camLookDown(Camera* cam, GLfloat deltaAngle);
void camLookLeft(Camera* cam, GLfloat deltaAngle);
void camLookRight(Camera* cam, GLfloat deltaAngle);

#endif