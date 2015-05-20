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
#include "Models.h"
#include "Camera.h"
#include "Loader/ImageLoader.h"

const int windowWidth = 800;
const int windowHeight = 600;

Camera cam;
GLuint texHouse, texRoof, texGround;

//***********************************/

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		cam.X, cam.Y, cam.Z,
		cam.X + cam.fwdX, cam.Y + cam.fwdY, cam.Z + cam.fwdZ,
		0, 1, 0);

	drawGround(texGround);

	glTranslatef(0, 0, -60);	

	drawHouse(0, 0, -20,	15, 7, 8,	texHouse, texRoof);
	drawHouse(20, 0, -4,	10, 8, 12,	texHouse, texRoof);
	drawHouse(-18, 0, 30,	20, 20, 40,	texHouse, texRoof);

    glutSwapBuffers();  // SWAP visible & drawing buffers
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
	texHouse = imgLoadBitmapToTexture("Texture/house.bmp");
	texRoof = imgLoadBitmapToTexture("Texture/roof.bmp");
	texGround= imgLoadBitmapToTexture("Texture/piste_snow.bmp");
}

void init() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("ICT289 Topic  - 3D houses n grass");

	glutDisplayFunc(display);
	glutSpecialFunc(keyFunc);
	glutKeyboardFunc(keyFunc2);
	//glutPassiveMotionFunc(mouseMoveHandler);

	// Set up view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, ((float)windowWidth / windowHeight), 1, 500);	// Near must be > 0! (?)

	glEnable(GL_DEPTH_TEST);

	// Init camera
	cam = camWithDefaults();
	cam.Y = 1.68f;	// Player eyes height

	//loadModels();
	loadTextures();
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Switch over to modelview matrix now that projection has been set up
    glMatrixMode(GL_MODELVIEW);	

	glClearColor(0, 0, 0, 0);

}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutMainLoop();

    return 0;
}
