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

GLint winWidth = 800, winHeight = 800, gameState = 0, pause = 0, turn = 1;

//Declare a world containing all objects
Camera myCamera;
Light myLight;
Table myTable;
Ball myBall;
StartMenu myStartMenu;

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
	pause = 0;
	turn = 1;
	glFlush();
	glutPostRedisplay();
}

void close(void) {
	exit(1);
}

void display(void) {

	//Game has 3 states: 0 - Start menu. 1 - Game is running. 2 - Game is over show score.
	if (gameState == 0) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		//Display the menu.
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);

		myStartMenu.drawStartMenu();
	}
	else if (gameState == 1) {
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix(); //Sets 3D view
		// Draw Table
		myTable.draw_table();
		myBall.draw();
	}

	else if (gameState == 2) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && running == 0) {
		running = 1;
		game_loop(1);
	}
	glutPostRedisplay();
}

void game_loop(int gameState) {
	//rotate the camera to the opposite side
	if(pause == 1){
		myCamera.rotate(0.0, 1.0, 0.0, 2.0);
		if(turn == 1 && myCamera.eye.z <= -5){
			pause = 0;
			turn = 2;
		}else if (turn == 2 && myCamera.eye.z >= 5){
			pause = 0;
			turn = 1;
		}
	}

	else{
		//update ball position
		myBall.translate(myBall.xSpeed, 0, myBall.zSpeed);
		myBall.xPosition += myBall.xSpeed;
		myBall.zPosition += myBall.zSpeed;

		myBall.rotate_mc(1, 0, 0, myBall.zSpeed*-500);
		myBall.rotate_mc(0, 0, 1, myBall.xSpeed*500);

		//Check bounds for collision
		if(myBall.xPosition >= 0.95){
			myBall.xSpeed = -0.01;
		}
		if(myBall.xPosition <= -0.95){
			myBall.xSpeed = 0.01;
		}

		//Check bounds for endgame
		if(myBall.zPosition >= 2.0 || myBall.zPosition <= -2){
			myBall.zSpeed = -myBall.zSpeed;
			pause = 1;
			//running = 0;
		}

		//Check bounds for paddle collision


	}
	if (gameState == 1) {
    	glutTimerFunc(40, game_loop, 1);  // callback every 40 ms
    }
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
	glutMouseFunc(mouseAction);
	glutKeyboardFunc(keyDown);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

