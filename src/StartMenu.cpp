/*
 * startMenu.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: Eric
 */

#include "StartMenu.hpp"

StartMenu::StartMenu() { }

void StartMenu::drawStartMenu() {

	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-winWidth / 4, 0.0);
	glVertex2f(winWidth / 4, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(0.0, -winHeight / 4);
	glVertex2f(0.0, winHeight / 4);
	glEnd();

	glutPostRedisplay();
}
