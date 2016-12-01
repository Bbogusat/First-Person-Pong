/**
 *	CP411 First Person Pong
 *	Ben and Eric
 */

#include "glsl/Angel.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "glaux.h" // for reading bmp files#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "mesh.hpp"
#include "StartMenu.hpp"
#include "EndGame.hpp"
#include "pixmap/RGBpixmap.h"
#include <windows.h>
#include <mmsystem.h>

RGBpixmap pix[6];   // make six pixmaps

GLint winWidth = 600, winHeight = 600, gameState = 0, pause = 0, turn = 2;
static const int numPaddles = 2;

//Declare a world containing all objects
Camera myCamera;
Light myLight;
Table myTable;
Ball myBall;
Paddle myPaddles[numPaddles];
StartMenu myStartMenu;
EndGame myEndGame;

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
	pix[0].readBMPFile("Pong table.bmp");
	pix[0].setTexture(0);

	pix[1].readBMPFile("tennisball.bmp");
	pix[1].setTexture(1);

	pix[2].readBMPFile("Wood.bmp");
	pix[2].setTexture(2);

	pix[3].readBMPFile("table_texture.bmp");
	pix[3].setTexture(3);

	myTable.setTextureID(0, 0);
	myTable.setTextureID(1, 2);
	myTable.setTextureID(2, 3);

	myBall.setTextureID(1);

	for (int i = 0; i < numPaddles; i++) {
		myPaddles[i] = Paddle(i + 1);
		myPaddles[i].setTextureID(2);
	}
}

void reset(void) {
	glutIdleFunc(NULL);
	gameState = 0;
	pause = 0;
	turn = 2;
	glFlush();
	glutPostRedisplay();
}

void close(void) {
	exit(1);
}
void turn_swap(void) {
	if (turn == 1) {
		turn = 2;
	} else if (turn == 2) {
		turn = 1;
	}
}

void game_over(void) {
	printf("\n---Game Over---\n");
	fflush(stdout);
	gameState = 2;
}

void paddle_collision(void) {
	std::vector<Point> bounds = myPaddles[turn - 1].getBounds();
	if (bounds[0].z < 0) {
		if (((myBall.zPosition - (myBall.scaledRadius * 1.25)) <= bounds[0].z)
				&& (bounds[0].x >= myBall.xPosition)
				&& (myBall.xPosition >= bounds[1].x)) {
			pause = 1;
			myBall.zSpeed = -myBall.zSpeed*1.05;
			myBall.xSpeed = myBall.xSpeed*(2);
			turn_swap();
		} else if (myBall.zPosition <= bounds[0].z) {
			game_over();
		}

	} else if (bounds[0].z > 0) {
		if (((myBall.zPosition + (myBall.scaledRadius * 1.25)) >= bounds[0].z)
				&& (bounds[0].x >= myBall.xPosition)
				&& (myBall.xPosition >= bounds[1].x)) {
			pause = 1;
			myBall.zSpeed = -myBall.zSpeed*1.05;
			myBall.xSpeed = myBall.xSpeed*(2);
			turn_swap();
		} else if (myBall.zPosition >= bounds[0].z) {
			game_over();
		}
	}
}
void display(void) {

	//Game has 3 states: 0 - Start menu. 1 - Game is running. 2 - Game is over show score.
	if (gameState == 0) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		//Display the menu.
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);

		myStartMenu.drawStartMenu();
	} else if (gameState == 1) {
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix(); //Sets 3D view
		// Draw Table
		glEnable(GL_TEXTURE_2D);
		myTable.draw_table();
		myBall.draw();

		for (int i = 0; i < numPaddles; i++) {
			myPaddles[i].draw();
		}
		glDisable(GL_TEXTURE_2D);
	} else if (gameState == 2) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		//Display the menu.
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
		//Display the end game state.
		myEndGame.drawEndGame();
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && gameState == 0) {
		PlaySound(TEXT("Killers.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		gameState = 1;
		game_loop(gameState);
	}
	glutPostRedisplay();
}

void game_loop(int state) {
	//rotate the camera to the opposite side
	if (gameState == 1) {
		if (pause == 1) {
			myCamera.rotate(0.0, 1.0, 0.0, 5.0);
			fflush(stdout);
			if (turn == 1 && myCamera.eye.z <= -5) {
				fflush(stdout);
				pause = 0;
			} else if (turn == 2 && myCamera.eye.z >= 5) {
				fflush(stdout);
				pause = 0;
			}

		}

		//else{
		//update ball position
		myBall.translate(myBall.xSpeed, 0, myBall.zSpeed);

		myBall.rotate_mc(1, 0, 0, myBall.zSpeed * -500);
		myBall.rotate_mc(0, 0, 1, myBall.xSpeed * 500);

		//Check bounds for collision
		if (myBall.xPosition >= 0.95) {
			myBall.xSpeed = -0.01;
		}
		if (myBall.xPosition <= -0.95) {
			myBall.xSpeed = 0.01;
		}
		paddle_collision();
		glutTimerFunc(40, game_loop, state);  // callback every 40 ms
	}
	glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y) {
	std::vector<Point> check = myPaddles[turn - 1].getBounds();
	GLint mod;
	GLfloat maxleft, maxright;
	maxright = 0.6;
	maxleft = -0.6;

	bool right,left = false;
	if (turn == 2) {
		mod = 1;
		//printf("bounds = %f || %f \n", check[1].x + 0.1, maxright);
		//fflush(stdout);
		if((maxright - check[1].x) < 0.1){
			right = true;
		}
		if((check[0].x - 0.1) > maxleft){
			left = true;
		}
	} else if (turn == 1) {
		mod = -1;
		if((check[1].x + 0.1) < maxright){
			left = true;
		}
		if((check[0].x - 0.1) > maxleft){
			right = true;
		}
	}
	// Right
	if ((key == 'd') && right) {
		myPaddles[turn - 1].translate(0.1 * mod, 0, 0);
	}
	// Left
	if ((key == 'a') && left) {
		myPaddles[turn - 1].translate(-0.1 * mod, 0, 0);
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

