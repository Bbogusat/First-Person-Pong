/*
 * Table.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: Eric
 */

#include "Table.hpp"

Table::Table() {}

void Table::draw_table() {
	//draw surface with hockey texture
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin( GL_QUADS);
	glTexCoord2f(0., 0.); glVertex3f(1, 1, 2);
	glTexCoord2f(0., 1.); glVertex3f(1, 1, -2);
	glTexCoord2f(1., 1.); glVertex3f(-1, 1, -2);
	glTexCoord2f(1., 0.); glVertex3f(-1, 1, 2);
	glEnd();

	//Back table face
	glColor3f(0.5, 0.3, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, -2);
	glVertex3f(1, .5, -2);
	glVertex3f(-1, .5, -2);
	glVertex3f(-1, 1, -2);
	glEnd();

	//Left table face
	glBegin(GL_POLYGON);
	glVertex3f(-1, 1, 2);
	glVertex3f(-1, 1, -2);
	glVertex3f(-1, .5, -2);
	glVertex3f(-1, .5, 2);
	glEnd();

	//Right table face
	glBegin(GL_POLYGON);
	glVertex3f(1, .5, 2);
	glVertex3f(1, .5, -2);
	glVertex3f(1, 1, -2);
	glVertex3f(1, 1, 2);
	glEnd();

	//Front table face
	glBegin(GL_POLYGON);
	glVertex3f(1, .5, 2);
	glVertex3f(1, 1, 2);
	glVertex3f(-1, 1, 2);
	glVertex3f(-1, .5, 2);
	glEnd();

	//Front Right leg
	//Back leg face
	glColor3f(0.7, 0.3, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1, .5, 1.8);
	glVertex3f(1, -1, 1.8);
	glVertex3f(.8, -1, 1.8);
	glVertex3f(.8, .5, 1.8);
	glEnd();

	//Left leg face
	glBegin(GL_POLYGON);
	glVertex3f(.8, .5, 2);
	glVertex3f(.8, .5, 1.8);
	glVertex3f(.8, -1, 1.8);
	glVertex3f(.8, -1, 2);
	glEnd();

	//Right leg face
	glBegin(GL_POLYGON);
	glVertex3f(1, -1, 2);
	glVertex3f(1, -1, 1.8);
	glVertex3f(1, .5, 1.8);
	glVertex3f(1, .5, 2);
	glEnd();

	//Front leg face
	glBegin(GL_POLYGON);
	glVertex3f(1, -1, 2);
	glVertex3f(1, .5, 2);
	glVertex3f(.8, .5, 2);
	glVertex3f(.8, -1, 2);
	glEnd();

	//Back Left leg
	//Back leg face
	glColor3f(0.7, 0.3, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-.8, .5, -2);
	glVertex3f(-.8, -1, -2);
	glVertex3f(-1, -1, -2);
	glVertex3f(-1, .5, -2);
	glEnd();

	//Left leg face
	glBegin(GL_POLYGON);
	glVertex3f(-1, .5, -1.8);
	glVertex3f(-1, .5, -2);
	glVertex3f(-1, -1, -2);
	glVertex3f(-1, -1, -1.8);
	glEnd();

	//Right leg face
	glBegin(GL_POLYGON);
	glVertex3f(-.8, -1, -1.8);
	glVertex3f(-.8, -1, -2);
	glVertex3f(-.8, .5, -2);
	glVertex3f(-.8, .5, -1.8);
	glEnd();

	//Front leg face
	glBegin(GL_POLYGON);
	glVertex3f(-.8, -1, -1.8);
	glVertex3f(-.8, .5, -1.8);
	glVertex3f(-1, .5, -1.8);
	glVertex3f(-1, -1, -1.8);
	glEnd();

	//Back Right leg
	//Back leg face
	glColor3f(0.7, 0.3, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1, .5, -2);
	glVertex3f(1, -1, -2);
	glVertex3f(.8, -1, -2);
	glVertex3f(.8, .5, -2);
	glEnd();

	//Left leg face
	glBegin(GL_POLYGON);
	glVertex3f(.8, .5, -1.8);
	glVertex3f(.8, .5, -2);
	glVertex3f(.8, -1, -2);
	glVertex3f(.8, -1, -1.8);
	glEnd();

	//Right leg face
	glBegin(GL_POLYGON);
	glVertex3f(1, -1, -1.8);
	glVertex3f(1, -1, -2);
	glVertex3f(1, .5, -2);
	glVertex3f(1, .5, -1.8);
	glEnd();

	//Front leg face
	glBegin(GL_POLYGON);
	glVertex3f(1, -1, -1.8);
	glVertex3f(1, .5, -1.8);
	glVertex3f(.8, .5, -1.8);
	glVertex3f(.8, -1, -1.8);
	glEnd();

	//Front Left leg
	//Back leg face
	glColor3f(0.7, 0.3, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-.8, .5, 1.8);
	glVertex3f(-.8, -1, 1.8);
	glVertex3f(-1, -1, 1.8);
	glVertex3f(-1, .5, 1.8);
	glEnd();

	//Left leg face
	glBegin(GL_POLYGON);
	glVertex3f(-1, .5, 2);
	glVertex3f(-1, .5, 1.8);
	glVertex3f(-1, -1, 1.8);
	glVertex3f(-1, -1, 2);
	glEnd();

	//Right leg face
	glBegin(GL_POLYGON);
	glVertex3f(-.8, -1, 2);
	glVertex3f(-.8, -1, 1.8);
	glVertex3f(-.8, .5, 1.8);
	glVertex3f(-.8, .5, 2);
	glEnd();

	//Front leg face
	glBegin(GL_POLYGON);
	glVertex3f(-.8, -1, 2);
	glVertex3f(-.8, .5, 2);
	glVertex3f(-1, .5, 2);
	glVertex3f(-1, -1, 2);
	glEnd();

}

void Table::setTextureID(int index, int textureid) {
	textureID[index] = textureid;
}
