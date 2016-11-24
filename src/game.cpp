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

void init(void) {
	myLight.translate(1.5, 1.5, 1.5);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Smooth out lines
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	//load and set vertex and fragement shader
	ProgramObject = InitShader("vertexshader.txt","fragmentshader.txt");
	glUseProgram(0);

	/* load and and set textures when needed
	pix[0].makeCheckerboard();
	pix[0].setTexture(0);

	Ball->setTextureID(0, 0);
	Ball->setTextureID(1, 1);
	
	Table.Leg->textureID = 3;
	
	//register objects world, so that transfermations can be applied to the objects
    myWorld.list[1] = &myBall;
    myWorld.list[2] = &myTable;

    */
}


void reset(void) {
	glutIdleFunc(NULL);
	glUseProgram(0);
	view = 0;
	menu = 1;
	isShading = false;
	isTexture = false;
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable( GL_LIGHTING );
	glDisable(GL_LIGHT0);
	myWorld.reset();
	glFlush();
	glutPostRedisplay();
}

void close(void) {
	exit(1);
}

void display(void) {
	if (Game.state == 0) {
		//Display the menu.
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Camera.setProjectionMatrix(); //Sets 3D view
		//menu.draw();
		/*
		//draw sample coordinate frames
		glLineWidth(3);
		glBegin(GL_LINES);
		//x-axis
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(2, 0, 0);
		glVertex3f(0, 0, 0);
		//y-axis
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0, 2, 0);
		glVertex3f(0, 0, 0);
		//z-axis
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 0, 2);
		glVertex3f(0, 0, 0);
		glEnd();
		glLineWidth(1);
		*/

		//Game has 3 states: 0 - Opening menu. 1 - Game is running. 2 - Game is over show score.
		glFlush();
	}

	else if (Game.state == 1 and ) {
		//Display the game based on its states.
		//world.draw();
		//light.draw();
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//drawGame();
		glFlush();
	}

	else if (Game.state == 2) {
		//Display the end game state. 
		//gameover.draw();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix();  // change to 3D view
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pointClick == 1) {
		Xpoint = x - winWidth / 2;
		Ypoint = winHeight / 2 - y;
		Zpoint = 0;

		printf("Point Clicked: %f %f %f \n", Xpoint, Ypoint, Zpoint);

	}
	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;

	glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y){

	//forward
	if (key == 'w'){
	    position += direction * deltaTime * speed;
	}
	// Move backward
	if (key == 's'){
	    position -= direction * deltaTime * speed;
	}
	// Right
	if (key == 'd'){
	    position += right * deltaTime * speed;
	}
	// Left
	if (key == 'a'){
	    position -= right * deltaTime * speed;
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
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutKeyboardFunc(keyDown);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

