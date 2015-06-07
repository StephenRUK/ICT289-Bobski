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
#include "Camera.h"
#include "Loader/ImageLoader.h"
#include "GameObject.h"
#include "Scene.h"
#include "Physics/CollisionResolution.h"

#include "Loader/ObjLoader.h"

const int windowWidth = 1280;
const int windowHeight = 720;

Camera cam;

GameObject *sBox;

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

void checkCollisions(){
	SceneItem* cItem1;
	SceneItem* cItem2;

	int collisionTrue = 0;

	if (scene.first != NULL){

		cItem1 = scene.first;

		while (cItem1 != NULL){

			cItem2 = scene.first;

			while (cItem2 != NULL) {

				if (cItem1 != cItem2) {
					collisionTrue = cResCheckCollision(&(cItem1->obj->bbox), &(cItem2->obj->bbox));
				}
				if (collisionTrue == 1){
					cResResolveCollision(cItem1->obj, cItem2->obj);
				}

				cItem2 = cItem2->next;
			}

			cItem1 = cItem1->next;

		}
	}
}

void moveSkyBox(){

	sBox->transform.position[0] = cam.player->transform.position[0];
	sBox->transform.position[1] = cam.player->transform.position[1] + 2;
	sBox->transform.position[2] = cam.player->transform.position[2];
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

	moveSkyBox();

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


	//drawGround(texGround);

	//glTranslatef(0, 0, -60);
	checkCollisions();

	// Draw skybox
	glDepthMask(GL_FALSE);
	gameObjDrawModel(sBox);
	glDepthMask(GL_TRUE);

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
		ball->transform.position[2] = *(cam.Z) + cam.fwdX*0.25f;

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


/*void loadTextures() {
	texGround= imgLoadBitmapToTexture("Resources/piste_snow.bmp");
}*/

void initGameObjects() {
	GameObject *obj;


	//
	//Skybox
	//
	sBox = gameObjCreate("Resources/skybox2.obj", "Resources/skybox.bmp");

	mathVector3MultiplyScalar(50, sBox->transform.scale, sBox->transform.scale);

	sBox->physics.isKinetic = 0;
	
	//
	//Ground
	//

	obj = gameObjCreate("Resources/box.obj", "Resources/piste_snow.bmp");
	gameObjScale(obj, 500, 0.1, 500);
	/*
	obj->transform.scale[0] = 500;
	obj->transform.scale[1] = 0.1;
	obj->transform.scale[2] = 500;
	*/
	obj->transform.position[1] = -1;
	
	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Sponge Test
	//
	obj = gameObjCreate("Resources/spongebob.obj", "Resources/spongebob.bmp");
	gameObjScale(obj, 2, 2, 2);

	//mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);

	obj->transform.position[2] = -10;
	obj->physics.gravityFactor = 1;

	sceneAddItem(&scene, obj);

	//
	// Sponge 1
	//
	obj = gameObjCreate("Resources/spongebob.obj", "Resources/spongebob.bmp");	
	obj->transform.position[0] = -6;
	obj->transform.position[1] = 4;
	obj->transform.position[2] = -24;

	obj->physics.gravityFactor = 0;

	mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);
	sceneAddItem(&scene, obj);

	//
	// Box Test 1
	//

	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");
	obj->transform.position[1] = 35;
	obj->transform.position[2] = -20;
	mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);

	sceneAddItem(&scene, obj);

	//
	// Box Test 2
	//

	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");
	
	obj->transform.position[0] = -10;
	obj->transform.position[1] = 15;
	obj->transform.position[2] = -20;
	mathVector3MultiplyScalar(5, obj->transform.scale, obj->transform.scale);

	obj->physics.acceleration[0] = -0.5;

	sceneAddItem(&scene, obj);

	//
	// Box 1
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -2;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -26;
	mathVector3MultiplyScalar(4, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 2
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -6;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -26;
	mathVector3MultiplyScalar(4, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 3
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -6;
	obj->transform.position[1] = 4;
	obj->transform.position[2] = -26;
	mathVector3MultiplyScalar(4, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 4
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -6;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -22;
	mathVector3MultiplyScalar(4, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 5
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -7;
	obj->transform.position[1] = 4;
	obj->transform.position[2] = -22;
	mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 6
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -5;
	obj->transform.position[1] = 4;
	obj->transform.position[2] = -22;
	mathVector3MultiplyScalar(2, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 7
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -4.5;
	obj->transform.position[1] = 4;
	obj->transform.position[2] = -21;
	mathVector3MultiplyScalar(1, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Box 8
	//


	obj = gameObjCreate("Resources/box.obj", "Resources/house.bmp");

	obj->transform.position[0] = -4.5;
	obj->transform.position[1] = 5;
	obj->transform.position[2] = -21;
	mathVector3MultiplyScalar(1, obj->transform.scale, obj->transform.scale);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Wall
	//

	obj = gameObjCreate("Resources/wall.obj", "Resources/wall.bmp");

	obj->transform.position[0] = -25;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -30;
	obj->transform.rotationAngles[1] = 90.0f;

	//mathVector3MultiplyScalar(0.05f, obj->transform.scale, obj->transform.scale);
	gameObjScale(obj, 0.05f, 0.05f, 0.05f);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Wall 2
	//

	obj = gameObjCreate("Resources/wall.obj", "Resources/wall.bmp");

	obj->transform.position[0] = -8;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -30;
	obj->transform.rotationAngles[1] = 90.0f;
	
	gameObjScale(obj, 0.05f, 0.05f, 0.05f);

	obj->physics.isKinetic = 0;

	sceneAddItem(&scene, obj);

	//
	// Wall 3
	//

	obj = gameObjCreate("Resources/wall.obj", "Resources/wall.bmp");

	obj->transform.position[0] = 8;
	obj->transform.position[1] = 0;
	obj->transform.position[2] = -20;
	obj->transform.rotationAngles[1] = 180.0f;
	
	gameObjScale(obj, 0.05f, 0.05f, 0.05f);

	obj->physics.isKinetic = 0;

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

	//loadTextures();
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
