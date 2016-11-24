/**
 *	CP411 First Person Pong
 *	Ben and Eric
 */

#include "glsl/Angel.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "glaux.h" // for reading bmp files

#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "mesh.hpp"

#include "pixmap/RGBpixmap.h"

RGBpixmap pix[6];   // make six pixmaps

GLint winWidth = 800, winHeight = 800, gameState = 1, moving = 0, xBegin = 0;

//Declare a world containing all objects
Camera myCamera;
Light myLight;
Table myTable;
Ball myBall;

void game_loop(int); // game animation loop

void init(void) {
	myLight.translate(1.5, 1.5, 1.5);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Smooth out lines
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	// load and and set textures when needed
	pix[0].readBMPFile("hockey.bmp");
	pix[0].setTexture(0);
	myTable.setTextureID(0, 0);
	
	pix[1].readBMPFile("tennisball.bmp");
	pix[1].setTexture(1);
	myBall.setTextureID(1);
}

void reset(void) {
	glutIdleFunc(NULL);
	gameState = 0;
	//view = 0;
	//menu = 1;
	glFlush();
	glutPostRedisplay();
}

void close(void) {
	exit(1);
}

void display(void) {

	//Game has 3 states: 0 - Opening menu. 1 - Game is running. 2 - Game is over show score.
	if (gameState == 0) {
		//Display the menu.
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Camera.setProjectionMatrix(); //Sets 3D view
		//menu.draw();
	}
	else if (gameState == 1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix(); //Sets 3D view
		// Draw Table
		myTable.draw_table();
		myBall.draw();
	}

	else if (gameState == 2) {
		//Display the end game state.
		//gameover.draw();
	}

	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		xBegin = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}

	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;
	theta = (xBegin - x < 0) ? 1 : -1;
	myCamera.rotate(0.0, 1.0, 0.0, theta * 0.5);
	glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y) {

	//forward
	if (key == 'w') {
		//position += direction * deltaTime * speed;
	}
	// Move backward
	if (key == 's') {
		//position -= direction * deltaTime * speed;
	}
	// Right
	if (key == 'd') {
		//position += right * deltaTime * speed;
	}
	// Left
	if (key == 'a') {
		//position -= right * deltaTime * speed;
	}

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("CP411 First Person Pong");
	glewInit(); // for using GSLS
	init();

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutKeyboardFunc(keyDown);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

