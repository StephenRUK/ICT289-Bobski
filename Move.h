#ifndef MOVE_H
#define MOVE_H

#include "Includes.h"

typedef struct Move {
	GLfloat X, Y, Z;
	GLfloat fwdX, fwdY, fwdZ;
	GLfloat upX, upY, upZ;

	GLfloat yaw, pitch;
	GLfloat maxPitch;

} Move;

Move movWithDefaults();

void movWalkForwards(Move* mov, GLfloat distance);
void movWalkBackwards(Move* mov, GLfloat distance);
void movStrafeLeft(Move* mov, GLfloat distance);
void movStrafeRight(Move* mov, GLfloat distance);

void movLookUp(Move* mov, GLfloat deltaAngle);
void movLookDown(Move* mov, GLfloat deltaAngle);
void movLookLeft(Move* mov, GLfloat deltaAngle);
void movLookRight(Move* mov, GLfloat deltaAngle);

#endif