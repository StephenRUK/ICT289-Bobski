#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"

typedef struct Camera {
	GLfloat X, Y, Z;
	GLfloat fwdX, fwdY, fwdZ;
	GLfloat upX, upY, upZ;
	float tSpeed;

	GLfloat yaw, pitch;
	GLfloat maxPitch;

} Camera;

Camera camWithDefaults();

void camWalkForwards(Camera* cam, GLfloat distance);
void camWalkBackwards(Camera* cam, GLfloat distance);
void camStrafeLeft(Camera* cam, GLfloat distance);
void camStrafeRight(Camera* cam, GLfloat distance);

void camLookUp(Camera* cam, GLfloat deltaAngle);
void camLookDown(Camera* cam, GLfloat deltaAngle);
void camLookLeft(Camera* cam, GLfloat deltaAngle);
void camLookRight(Camera* cam, GLfloat deltaAngle);

#endif