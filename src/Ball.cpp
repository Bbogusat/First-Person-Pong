/*
 *	File: Ball.cpp
 */

#include "Ball.hpp"
#include <stdio.h>
using namespace std;

Ball::Ball(){
	radius = 0.5;
	stacks = 20;
	splices = 20;
	r = 1.0;
	b = 1.0;
	g = 1.0;
	xSpeed = .05;
	zSpeed = .1;
	this->scale_change(-.85);
	this->translate(0, 1.08, 0);

	quad = gluNewQuadric();

	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluQuadricNormals(quad, GLU_SMOOTH);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/*
 * set_colour
 * a function to set the colour of the planet
 * Parameters:
 * 	red: the amount of red
 * 	green: the amount of green
 * 	blue: the amount of blue
 * Returns:
 * 	none
 */
void Ball::set_colour(GLfloat red, GLfloat green, GLfloat blue){
	r = red;
	g = green;
	b = blue;
}

/*
 * draw
 * the function that draws the planet
 * Parameters:
 * 	none
 * Returns:
 * 	none
 */
void Ball::draw(){
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	glColor3f(r, g, b);
	gluSphere(quad, radius, splices, stacks);
	glPopMatrix();
}

void Ball::setTextureID(int textureid) {
	textureID = textureid;
}

