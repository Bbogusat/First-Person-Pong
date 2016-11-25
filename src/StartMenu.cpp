/*
 * startMenu.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: Eric
 */

#include "StartMenu.hpp"

StartMenu::StartMenu() {
}

void StartMenu::drawStartMenu() {

	//Draw the P
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(-250, 250);
	glVertex2i(-250, 70);
	glVertex2i(-215, 70);
	glVertex2i(-215, 150);
	glVertex2i(-150, 150);
	glVertex2i(-150, 250);
	glVertex2i(-250, 250);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(-215, 215);
	glVertex2i(-215, 185);
	glVertex2i(-185, 185);
	glVertex2i(-185, 215);
	glEnd();

	//Draw the O
	glColor3f(1.0, 1.0, 1.0);
	glRecti(-120, 250, -20, 70);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(-85, 215, -55, 105);

	//Draw the N
	glColor3f(1.0, 1.0, 1.0);
	glRecti(10, 250, 130, 70);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(45, 250);
	glVertex2i(95, 250);
	glVertex2i(95, 125);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2i(45, 70);
	glVertex2i(95, 70);
	glVertex2i(45, 195);
	glEnd();

	//Draw the G
	glColor3f(1.0, 1.0, 1.0);
	glRecti(160, 250, 260, 70);

	glColor3f(0.0, 0.0, 0.0);
	glRecti(190, 215, 260, 150);
	glRecti(190, 150, 230, 105);

	glColor3f(1.0, 1.0, 1.0);
	glRecti(210, 150, 230, 130);

	glutPostRedisplay();
}

