/*
*   ICT 289 - Project Bobski
*	Semester 1, 2015
*
*   Authors: Stephen Randles
*/

#define FREEGLUT_LIB_PRAGMAS 1

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

//***********************************/

void doPhysics() {

	int newElapsedTime = glutGet(GLUT_ELAPSED_TIME);
	dt = (newElapsedTime - elapsedTime) / 1000;
	elapsedTime = (float)newElapsedTime;

	//
	// Loop through GameObjects
	//
	if (scene.first != NULL) {
		SceneItem* item = scene.first;
		while (item != NULL) {
			gameObjUpdatePhysics(item->obj, dt);

			item = item->next;
		}
	}
	
}

void drawScene() {
	if (scene.first != NULL) {
		SceneItem* item = scene.first;
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
	// Render
	//
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		cam.X, cam.Y, cam.Z,
		cam.X + cam.fwdX, cam.Y + cam.fwdY, cam.Z + cam.fwdZ,
		0, 1, 0);

	drawGround(texGround);

	glTranslatef(0, 0, -60);
	
	drawScene();

    glutSwapBuffers();
    glFlush();
}

void keyFunc(int keyCode, int x, int y) {
	float moveSpeed = 3;

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

	switch (keyCode) {
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
	GameObject *box1, *box2, *box3, *spongebob, *wall;

	//
	// Sponge!
	//
	spongebob = gameObjCreate("Resources/spongebob.obj", "Resources/spongebob.bmp");
	mathVector3MultiplyScalar(2, spongebob->transform.scale, spongebob->transform.scale);
	spongebob->physics.gravityFactor = 0;

	sceneAddItem(&scene, spongebob);

	//
	// Box 1
	//

	box1 = gameObjCreate("Resources/box.obj", "Resources/house.bmp");
	box1->transform.position[1] = 35;
	mathVector3MultiplyScalar(2, box1->transform.scale, box1->transform.scale);

	sceneAddItem(&scene, box1);

	//
	// Box 2
	//

	box2 = gameObjCreate("Resources/box.obj", "Resources/house.bmp");
	
	box2->transform.position[0] = -10;
	box2->transform.position[1] = 15;
	mathVector3MultiplyScalar(5, box2->transform.scale, box2->transform.scale);

	box2->physics.acceleration[0] = -0.5;

	sceneAddItem(&scene, box2);

	//
	// Box 3
	//


	box3 = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	box3->transform.position[0] = -10;
	box3->transform.position[1] = 0;
	box3->transform.position[2] = -14;
	mathVector3MultiplyScalar(4, box3->transform.scale, box3->transform.scale);

	box3->physics.gravityFactor = 0;

	sceneAddItem(&scene, box3);

	//
	// Wall
	//

	wall = gameObjCreate("Resources/wall.obj", "Resources/wall.bmp");

	wall->transform.position[0] = -10;
	wall->transform.position[1] = 0;
	wall->transform.position[2] = -20;
	wall->transform.rotationAngles[1] = 90.0f;
	mathVector3MultiplyScalar(0.05f, wall->transform.scale, wall->transform.scale);

	wall->physics.isKinetic = 0;
	wall->physics.gravityFactor = 0;

	sceneAddItem(&scene, wall);
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
	cam.Y = 1.68f;	// Player eyes height

	loadTextures();
	initGameObjects();

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
