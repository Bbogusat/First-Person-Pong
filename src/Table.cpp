/*
 * Table.cpp
 *
 */

#include "Table.hpp"

Table::Table() {
	//Create table legs using a starting point.
	frontRightLeg = new Leg(GLfloat(1),GLfloat(.5),GLfloat(1.8));
	backLeftLeg = new Leg(GLfloat(-.8),GLfloat(.5), GLfloat(-2));
	backRightLeg = new Leg(GLfloat(1), GLfloat(.5), GLfloat(-2));
	frontLeftLeg = new Leg(GLfloat(-.8), GLfloat(.5), GLfloat(1.8));
}

void Table::draw_table() {
	//draw surface with hockey texture
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBegin( GL_QUADS);
	glTexCoord2f(0., 0.); glVertex3f(1, 1, 2);
	glTexCoord2f(0., 1.); glVertex3f(1, 1, -2);
	glTexCoord2f(1., 1.); glVertex3f(-1, 1, -2);
	glTexCoord2f(1., 0.); glVertex3f(-1, 1, 2);
	glEnd();

	//Draw legs and set Wood texture
	frontRightLeg->setTextureID(textureID[1]);
	backLeftLeg->setTextureID(textureID[1]);
	frontLeftLeg->setTextureID(textureID[1]);
	backRightLeg->setTextureID(textureID[1]);
	frontRightLeg->draw_leg();
	backLeftLeg->draw_leg();
	backRightLeg->draw_leg();
	frontLeftLeg->draw_leg();

	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	//Back table face
	glBegin(GL_POLYGON);
	glTexCoord2f(0., 0.);
	glVertex3f(1, 1, -2);
	glTexCoord2f(0., 1.);
	glVertex3f(1, .5, -2);
	glTexCoord2f(1., 1.);
	glVertex3f(-1, .5, -2);
	glTexCoord2f(1., 0.);
	glVertex3f(-1, 1, -2);
	glEnd();

	//Left table face
	glBegin(GL_POLYGON);
	glTexCoord2f(0., 0.);
	glVertex3f(-1, 1, 2);
	glTexCoord2f(0., 1.);
	glVertex3f(-1, 1, -2);
	glTexCoord2f(1., 1.);
	glVertex3f(-1, .5, -2);
	glTexCoord2f(1., 0.);
	glVertex3f(-1, .5, 2);
	glEnd();

	//Right table face
	glBegin(GL_POLYGON);
	glTexCoord2f(0., 0.);
	glVertex3f(1, .5, 2);
	glTexCoord2f(0., 1.);
	glVertex3f(1, .5, -2);
	glTexCoord2f(1., 1.);
	glVertex3f(1, 1, -2);
	glTexCoord2f(1., 0.);
	glVertex3f(1, 1, 2);
	glEnd();

	//Front table face
	glBegin(GL_POLYGON);
	glTexCoord2f(0., 0.);
	glVertex3f(1, .5, 2);
	glTexCoord2f(0., 1.);
	glVertex3f(1, 1, 2);
	glTexCoord2f(1., 1.);
	glVertex3f(-1, 1, 2);
	glTexCoord2f(1., 0.);
	glVertex3f(-1, .5, 2);
	glEnd();

}

void Table::setTextureID(int index, int textureid) {
	textureID[index] = textureid;
}
