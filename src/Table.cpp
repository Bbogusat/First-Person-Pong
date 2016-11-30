/*
 * Table.cpp
 *
 */

#include "Table.hpp"

Table::Table() {}

void Table::draw_table() {
	//draw surface with hockey texture
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBegin( GL_QUADS);
	glTexCoord2f(0., 0.); glVertex3f(1, 1, 2);
	glTexCoord2f(0., 1.); glVertex3f(1, 1, -2);
	glTexCoord2f(1., 1.); glVertex3f(-1, 1, -2);
	glTexCoord2f(1., 0.); glVertex3f(-1, 1, 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	//Front Right leg
		//Back leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(1, .5, 1.8);
		glTexCoord2f(0., 1.); glVertex3f(1, -1, 1.8);
		glTexCoord2f(1., 1.); glVertex3f(.8, -1, 1.8);
		glTexCoord2f(1., 0.);glVertex3f(.8, .5, 1.8);
		glEnd();

		//Left leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(.8, .5, 2);
		glTexCoord2f(0., 1.); glVertex3f(.8, .5, 1.8);
		glTexCoord2f(1., 1.); glVertex3f(.8, -1, 1.8);
		glTexCoord2f(1., 0.); glVertex3f(.8, -1, 2);
		glEnd();

		//Right leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(1, -1, 2);
		glTexCoord2f(0., 1.); glVertex3f(1, -1, 1.8);
		glTexCoord2f(1., 1.); glVertex3f(1, .5, 1.8);
		glTexCoord2f(1., 0.); glVertex3f(1, .5, 2);
		glEnd();

		//Front leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(1, -1, 2);
		glTexCoord2f(0., 1.); glVertex3f(1, .5, 2);
		glTexCoord2f(1., 1.); glVertex3f(.8, .5, 2);
		glTexCoord2f(1., 0.); glVertex3f(.8, -1, 2);
		glEnd();

		//Back Left leg
		//Back leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-.8, .5, -2);
		glTexCoord2f(0., 1.); glVertex3f(-.8, -1, -2);
		glTexCoord2f(1., 1.); glVertex3f(-1, -1, -2);
		glTexCoord2f(1., 0.); glVertex3f(-1, .5, -2);
		glEnd();

		//Left leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-1, .5, -1.8);
		glTexCoord2f(0., 1.); glVertex3f(-1, .5, -2);
		glTexCoord2f(1., 1.); glVertex3f(-1, -1, -2);
		glTexCoord2f(1., 0.); glVertex3f(-1, -1, -1.8);
		glEnd();

		//Right leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-.8, -1, -1.8);
		glTexCoord2f(0., 1.); glVertex3f(-.8, -1, -2);
		glTexCoord2f(1., 1.); glVertex3f(-.8, .5, -2);
		glTexCoord2f(1., 0.); glVertex3f(-.8, .5, -1.8);
		glEnd();

		//Front leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-.8, -1, -1.8);
		glTexCoord2f(0., 1.); glVertex3f(-.8, .5, -1.8);
		glTexCoord2f(1., 1.); glVertex3f(-1, .5, -1.8);
		glTexCoord2f(1., 0.); glVertex3f(-1, -1, -1.8);
		glEnd();

		//Back Right leg
		//Back leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(1, .5, -2);
		glTexCoord2f(0., 1.); glVertex3f(1, -1, -2);
		glTexCoord2f(1., 1.); glVertex3f(.8, -1, -2);
		glTexCoord2f(1., 0.); glVertex3f(.8, .5, -2);
		glEnd();

		//Left leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(.8, .5, -1.8);
		glTexCoord2f(0., 1.); glVertex3f(.8, .5, -2);
		glTexCoord2f(1., 1.); glVertex3f(.8, -1, -2);
		glTexCoord2f(1., 0.); glVertex3f(.8, -1, -1.8);
		glEnd();

		//Right leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(1, -1, -1.8);
		glTexCoord2f(0., 1.); glVertex3f(1, -1, -2);
		glTexCoord2f(1., 1.); glVertex3f(1, .5, -2);
		glTexCoord2f(1., 0.); glVertex3f(1, .5, -1.8);
		glEnd();

		//Front leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(1, -1, -1.8);
		glTexCoord2f(0., 1.); glVertex3f(1, .5, -1.8);
		glTexCoord2f(1., 1.); glVertex3f(.8, .5, -1.8);
		glTexCoord2f(1., 0.); glVertex3f(.8, -1, -1.8);
		glEnd();

		//Front Left leg
		//Back leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-.8, .5, 1.8);
		glTexCoord2f(0., 1.); glVertex3f(-.8, -1, 1.8);
		glTexCoord2f(1., 1.); glVertex3f(-1, -1, 1.8);
		glTexCoord2f(1., 0.); glVertex3f(-1, .5, 1.8);
		glEnd();

		//Left leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-1, .5, 2);
		glTexCoord2f(0., 1.); glVertex3f(-1, .5, 1.8);
		glTexCoord2f(1., 1.); glVertex3f(-1, -1, 1.8);
		glTexCoord2f(1., 0.); glVertex3f(-1, -1, 2);
		glEnd();

		//Right leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-.8, -1, 2);
		glTexCoord2f(0., 1.); glVertex3f(-.8, -1, 1.8);
		glTexCoord2f(1., 1.); glVertex3f(-.8, .5, 1.8);
		glTexCoord2f(1., 0.); glVertex3f(-.8, .5, 2);
		glEnd();

		//Front leg face
		glBegin(GL_POLYGON);
		glTexCoord2f(0., 0.); glVertex3f(-.8, -1, 2);
		glTexCoord2f(0., 1.); glVertex3f(-.8, .5, 2);
		glTexCoord2f(1., 1.); glVertex3f(-1, .5, 2);
		glTexCoord2f(1., 0.); glVertex3f(-1, -1, 2);
		glEnd();
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
