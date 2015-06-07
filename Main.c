/*
*   ICT 289 - Project Bobski
*	Semester 1, 2015
*
*   Authors: Stephen Randles
*/

#define FREEGLUT_LIB_PRAGMAS 1	// Stops Visual Studio from trying to load the debug binary freeglutd.lib (not installed & not needed)

#include <stdio.h>
#include <math.h>

#include "Includes.h"
#include "Models.h"
#include "Camera.h"
#include "Loader/ImageLoader.h"
#include "GameObject.h"
#include "Scene.h"

#include "Loader/ObjLoader.h"

const int windowWidth = 1280;
const int windowHeight = 720;

Camera cam;

float elapsedTime;	// Milliseconds elapsed since application start
float dt = 0;	// Seconds elapsed between loops

SceneList scene;	// Contains all game objects in the scene

GLuint texGround;	// Debug

//
// Player parameters
// TODO: Move to separate data structure (Player struct?)
//
float playerThrowSpeed = 8;		// Metres per second
float playerThrowAngle = 45;	// Degrees over camera pitch angle (relative to view)

//
// Light parameters
//

// Light0: Key light, aka. "the sun"
GLfloat lightPos0[] = { 60.0, 20.0, 30.0, 0.0 };
GLfloat lightColour0[] = { 0.8, 0.8, 0.8, 1.0 };

// Light1: Side light
GLfloat lightPos1[] = { 10.0, 1.5, 0.0, 0.0 };
GLfloat lightColour1[] = { 0.15, 0.15, 0.15, 1.0 };

// Light1: Back light
GLfloat lightPos2[] = { 0.0, 2.0, -2.0, 0.0 };
GLfloat lightColour2[] = { 0.2, 0.2, 0.2, 1.0 };

//***********************************/

void doPhysics() {
	int newElapsedTime;
	SceneItem* item;

	newElapsedTime = glutGet(GLUT_ELAPSED_TIME);
	dt = (newElapsedTime - elapsedTime) / 1000;
	elapsedTime = (float)newElapsedTime;

	//
	// Loop through GameObjects
	//
	if (scene.first != NULL) {
		item = scene.first;
		while (item != NULL) {
			gameObjUpdatePhysics(item->obj, dt);

			item = item->next;
		}
	}
	
}

void drawScene() {
	SceneItem* item;

	if (scene.first != NULL) {
		item = scene.first;
		while (item != NULL) {
			gameObjDrawModel(item->obj);

			item = item->next;
		}
	}
}

void display(void) {
	//
	// Physics
	//
	doPhysics();


	//
	// Collisions
	//

	// Detect collisions

	// Resolve collisions


	//
	// Render
	//
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		*(cam.X), *(cam.Y), *(cam.Z),
		*(cam.X) + cam.fwdX, *(cam.Y) + cam.fwdY, *(cam.Z) + cam.fwdZ,
		0, 1, 0);

	//
	// Lighting
	//
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightColour0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour0);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColour1);

	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColour2);

	//-----------------------


	drawGround(texGround);

	//glTranslatef(0, 0, -60);
	
	drawScene();

    glutSwapBuffers();
    glFlush();
}

void keyFunc(int keyCode, int x, int y) {
	float moveSpeed = 0.8;	// Metres moved on each keypress

	switch (keyCode) {
	case GLUT_KEY_LEFT:
		camStrafeLeft(&cam, moveSpeed);
		break;
	case GLUT_KEY_RIGHT:
		camStrafeRight(&cam, moveSpeed);
		break;
	case GLUT_KEY_UP:
		camWalkForwards(&cam, moveSpeed);
		break;
	case GLUT_KEY_DOWN:
		camWalkBackwards(&cam, moveSpeed);
		break;
	}

	glutPostRedisplay();		
}

void keyFunc2(unsigned char keyCode, int x, int y) {
	float turnSpeed = 0.05f;
	GameObject *ball;

	switch (keyCode) {

	//
	// Looking around. To (probably) be replaced with mouse controls.
	//
	case 'w':
		camLookUp(&cam, turnSpeed);
		break;
	case 'a':
		camLookLeft(&cam, turnSpeed);
		break;
	case 's':
		camLookDown(&cam, turnSpeed);
		break;
	case 'd':
		camLookRight(&cam, turnSpeed);
		break;

	//
	// Throw ball on space key press
	//
	case ' ':
		// Trigger function to create ball, set up position, init. velocity.

		ball = gameObjCreate("Resources/ball.obj", "Resources/ball.bmp");
		ball->transform.position[0] = *(cam.X) - 0.6;
		ball->transform.position[1] = *(cam.Y);
		ball->transform.position[2] = *(cam.Z);

		ball->physics.velocity[0] = cam.fwdX * playerThrowSpeed;
		ball->physics.velocity[1] = (cam.pitch + cos(playerThrowAngle)) * playerThrowSpeed;
		ball->physics.velocity[2] = cam.fwdZ * playerThrowSpeed;

		sceneAddItem(&scene, ball);

		break;

	}

	glutPostRedisplay();
}


int lastMouseX, lastMouseY;
void mouseMoveHandler(int x, int y) {
	float mouseSpeed = 0.001f;
	if (x - lastMouseX < 0) camLookLeft(&cam, mouseSpeed);
	if (x - lastMouseX > 0) camLookRight(&cam, mouseSpeed);

	if (y - lastMouseY < 0) camLookUp(&cam, mouseSpeed);
	if (y - lastMouseY > 0) camLookDown(&cam, mouseSpeed);

	glutPostRedisplay();

	lastMouseX = x;
	lastMouseY = y;
}


void loadTextures() {
	texGround= imgLoadBitmapToTexture("Resources/piste_snow.bmp");
}

void initGameObjects() {
	GameObject *obj;

	//
	// Sponge!
	//
	obj = gameObjCreate("Resources/spongebob.obj", "Resources/spongebob.bmp");
	mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);
	obj->transform.position[2] = -10;
	obj->physics.gravityFactor = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 1
	//

	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");
	obj->transform.position[1] = 35;
	obj->transform.position[2] = -20;
	mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);

	sceneAddItem(&scene, obj);

	//
	// Box 2
	//

	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");
	
	obj->transform.position[0] = -10;
	obj->transform.position[1] = 15;
	obj->transform.position[2] = -20;
	mathVector3MultiplyScalar(5, obj->transform.scale, obj->transform.scale);

	obj->physics.acceleration[0] = -0.5;

	sceneAddItem(&scene, obj);

	//
	// Box 3
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -10;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -14;
	mathVector3MultiplyScalar(4, obj->transform.scale, obj->transform.scale);

	obj->physics.gravityFactor = 0;

	sceneAddItem(&scene, obj);

	//
	// Wall
	//

	obj = gameObjCreate("Resources/wall.obj", "Resources/wall.bmp");

	obj->transform.position[0] = -25;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -30;
	obj->transform.rotationAngles[1] = 90.0f;
	mathVector3MultiplyScalar(0.05f, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;
	obj->physics.gravityFactor = 0;

	sceneAddItem(&scene, obj);
}

void idle() {
	glutPostRedisplay();
}

void init() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Project Bobski (alpha)");

	glutDisplayFunc(display);
	glutSpecialFunc(keyFunc);
	glutKeyboardFunc(keyFunc2);
	//glutPassiveMotionFunc(mouseMoveHandler);
	glutIdleFunc(idle);

	// Set up view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, ((float)windowWidth / windowHeight), 1, 500);	// Near must be > 0! (?)

	glEnable(GL_DEPTH_TEST);

	// Init camera
	cam = camWithDefaults();
	sceneAddItem(&scene, cam.player);

	loadTextures();
	initGameObjects();

	// Lighting and blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);


    // Switch over to modelview matrix now that projection has been set up
    glMatrixMode(GL_MODELVIEW);	

	glClearColor(0, 0, 0, 1);

}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutMainLoop();

    return 0;
}
