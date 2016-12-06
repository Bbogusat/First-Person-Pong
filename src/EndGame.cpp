/*
 * EndGame.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: Eric
 */

#include "EndGame.hpp"

EndGame::EndGame() {
}

void EndGame::drawEndGame() {
	//Draw the G
	glColor3f(1.0, 1.0, 1.0);
	glRecti(-250, 250, -150, 70);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(-220, 215, -150, 150);
	glRecti(-220, 150, -180, 105);

	glColor3f(1.0, 1.0, 1.0);
	glRecti(-200, 150, -180, 130);

	//Draw the A
	glColor3f(1.0, 1.0, 1.0);
	glRecti(-120, 250, -20, 70);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(-85, 215, -55, 160);
	glRecti(-85, 125, -55, 70);

	//Draw the M
	glColor3f(1.0, 1.0, 1.0);
	glRecti(10, 250, 180, 70);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(45, 250);
	glVertex2i(145, 250);
	glVertex2i(95, 125);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(45, 70);
	glVertex2i(95, 70);
	glVertex2i(45, 195);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(145, 70);
	glVertex2i(95, 70);
	glVertex2i(145, 195);
	glEnd();

	//Draw the E
	glColor3f(1.0, 1.0, 1.0);
	glRecti(210, 250, 310, 70);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(245, 215, 310, 175);
	glRecti(245, 105, 310, 145);
	glRecti(300, 145, 310, 175);

	//Draw the O
	glColor3f(1.0, 1.0, 1.0);
	glRecti(-250, 50, -150, -130);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(-215, 15, -185, -95);

	//Draw the V
	glColor3f(1.0, 1.0, 1.0);
	glRecti(-120, 50, 10, -130);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(-85, 50);
	glVertex2i(-25, 50);
	glVertex2i(-55, -95);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(-120, -130);
	glVertex2i(-65, -130);
	glVertex2i(-120, 50);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(10, -130);
	glVertex2i(-45, -130);
	glVertex2i(10, 50);
	glEnd();

	//Draw the E
	glColor3f(1.0, 1.0, 1.0);
	glRecti(40, 50, 140, -130);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(75, 15, 140, -25);
	glRecti(75, -55, 140, -95);
	glRecti(130, -25, 140, -55);

	//Draw the R
	glColor3f(1.0, 1.0, 1.0);
	glRecti(170, 50, 300, -130);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(205, 15, 265, -15);
	glRecti(205, -50, 230, -130);

	glBegin(GL_POLYGON);
	glVertex2i(300, -50);
	glVertex2i(300, -130);
	glVertex2i(265, -50);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(230, -130);
	glVertex2i(265, -130);
	glVertex2i(230, -50);
	glEnd();

	glutPostRedisplay();
}

