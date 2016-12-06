/**
 *	CP411 First Person Pong
 *	Ben and Eric
 */

#include "glsl/Angel.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "glaux.h"#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "mesh.hpp"
#include "StartMenu.hpp"
#include "EndGame.hpp"
#include "pixmap/RGBpixmap.h"
#include <windows.h>
#include <mmsystem.h>
#include <time.h>

RGBpixmap pix[4];   // make four pixmaps

GLint winWidth = 650, winHeight = 650, gameState = 0, pause = 0, turn = 2;
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
int randNum(int);

void init(void) {
	srand(time(NULL));
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
	myCamera.setDefaultCamera();
	myBall.setDefaultBall();
	myPaddles[0].setDefaultPaddle(1);
	myPaddles[1].setDefaultPaddle(2);
	glFlush();
	PlaySound(TEXT("Killers.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
int randNum(int max){
	int num = rand()%max + 1;
	return num;
}

void game_over(void) {
	printf("\n---Game Over---\n");
	fflush(stdout);
	gameState = 2;
}

void paddle_collision(void) {
	std::vector<Point> bounds = myPaddles[turn - 1].getBounds(); //Grabs the bounds of the current paddle
	if (bounds[0].z < 0) { //If it is the paddle on the negative side
		if (((myBall.zPosition - (myBall.scaledRadius * 1.25)) <= bounds[0].z)
				&& (bounds[0].x >= myBall.xPosition)
				&& (myBall.xPosition >= bounds[1].x)) {
			pause = 1;
			//Increase/decrease speed by a random number from -1% to 7%.
			myBall.zSpeed = -myBall.zSpeed*(((GLfloat(randNum(8))/GLfloat(100))-.01) + 1);
			//Increase rotation speed by a random number from 1-3.
			myBall.xSpeed = myBall.xSpeed*(randNum(3));
			turn_swap();
		} else if (myBall.zPosition <= bounds[0].z) {
			game_over();
		}

	} else if (bounds[0].z > 0) { //If it is the paddle on the positive side
		if (((myBall.zPosition + (myBall.scaledRadius * 1.25)) >= bounds[0].z)
				&& (bounds[0].x >= myBall.xPosition)
				&& (myBall.xPosition >= bounds[1].x)) {
			pause = 1;
			myBall.zSpeed = -myBall.zSpeed*(((GLfloat(randNum(8))/GLfloat(100))-.01) +1);
			myBall.xSpeed = myBall.xSpeed*(randNum(3));
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
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix(); //Sets 3D view
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
		//Display the menu.
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
		//Display the end game state.
		myEndGame.drawEndGame();
		PlaySound(NULL,0,0);
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
		gameState = 1;
		game_loop(gameState);
	}else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN
			&& gameState == 2) {
		reset();
	}
	glutPostRedisplay();
}

void game_loop(int state) {
	//rotate the camera to the opposite side
	if (gameState == 1) {
		if (pause == 1) {
			myCamera.rotate(0.0, 1.0, 0.0, 5.0);
			if (turn == 1 && myCamera.eye.z <= -5) {
				pause = 0;
			} else if (turn == 2 && myCamera.eye.z >= 5) {
				pause = 0;
			}

		}

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

	bool right = false,left = false;
	//Checking table bounds for the paddle in play
	if (turn == 2) {
		mod = 1;
		if((check[1].x) < maxright){
			right = true;
		}
		if((check[0].x) > maxleft){
			left = true;
		}
	} else if (turn == 1) {
		mod = -1;
		if((check[1].x) < maxright){
			left = true;
		}
		if((check[0].x) > maxleft){
			right = true;
		}
	}
	// Right if table bounds are met
	if ((key == 'd') && right) {
		myPaddles[turn - 1].translate(0.1 * mod, 0, 0);
	}
	// Left if table bounds are met
	if ((key == 'a') && left) {
		myPaddles[turn - 1].translate(-0.1 * mod, 0, 0);
	}
}

int main(int argc, char** argv) {
	PlaySound(TEXT("Killers.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("CP411 3D-Pong");
	glewInit(); // for using GSLS later
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

