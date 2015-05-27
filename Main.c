/*
*   ICT 289 - Project Bobski
*	Semester 1, 2015
*
*   Authors: Stephen Randles
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "Includes.h"
#include "Models.h"	// Will be removed once model loader has been implemented
#include "Camera.h"
#include "Loader/ImageLoader.h"
#include "GameObject.h"
#include "Scene.h"

#include "Loader/ObjLoader.h"

const int windowWidth = 800;
const int windowHeight = 600;

Camera cam;

float elapsedTime;	// Milliseconds elapsed since application start
float dt = 0;	// Seconds elapsed between loops

SceneList scene;	// Contains all game objects in the scene

GLuint texGround;	// Debug

//***********************************/

void doPhysics() {

	int newElapsedTime = glutGet(GLUT_ELAPSED_TIME);
	dt = (newElapsedTime - elapsedTime) / 1000;
	elapsedTime = newElapsedTime;

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

	//
	// Sponge!
	//
	Model spongebob;
	objLoadModel(&spongebob, "Resources/spongebob.obj", 4);
	spongebob.textureID = imgLoadBitmapToTexture("Resources/spongebob.bmp");
	
	Transform spongeTrans;
	transformSetDefaults(&spongeTrans);

	PhysicsObject spongePhysics;
	physObjSetDefaults(&spongePhysics);
	spongePhysics.gravityFactor = 0;

	GameObject* spongebobObj = gameObjCreate(&spongebob, &spongeTrans, &spongePhysics);

	sceneAddItem(&scene, spongebobObj);

	//
	// Box
	//

	Model boxModel;
	objLoadModel(&boxModel, "Resources/box.obj", 4);
	
	boxModel.textureID = imgLoadBitmapToTexture("Resources/house.bmp");

	Transform trans;
	transformSetDefaults(&trans);
	trans.position[1] = 35;
	mathVector3MultiplyScalar(2, trans.scale, trans.scale);

	PhysicsObject physics;
	physObjSetDefaults(&physics);

	GameObject* box = gameObjCreate(&boxModel, &trans, &physics);

	sceneAddItem(&scene, box);

	//
	// Box 2
	//
	transformSetDefaults(&trans);
	trans.position[0] = -10;
	trans.position[1] = 15;
	mathVector3MultiplyScalar(5, trans.scale, trans.scale);

	physObjSetDefaults(&physics);
	physics.acceleration[0] = -0.5;

	GameObject* box2 = gameObjCreate(&boxModel, &trans, &physics);

	sceneAddItem(&scene, box2);

	//
	// Box 3
	//
	transformSetDefaults(&trans);
	trans.position[0] = 25;
	trans.position[1] = 15;
	mathVector3MultiplyScalar(5, trans.scale, trans.scale);

	physObjSetDefaults(&physics);
	physics.acceleration[1] = 9.81f;	// Cancels out gravity, so just "hovers"

	GameObject* box3 = gameObjCreate(&boxModel, &trans, &physics);

	sceneAddItem(&scene, box3);

}

void idle() {
	glutPostRedisplay();
}

void init() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("ICT289 Topic  - 3D houses n grass");

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
