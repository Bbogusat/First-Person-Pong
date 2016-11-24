/*
 *	Name: 
 *	ID: 
 *	Class: CP411
 *	Assignment: 3
 *	Date: 11/2/2013
 *	File: Planet.cpp
 */

#include "Ball.hpp"
#include <stdio.h>
using namespace std;

Ball::Ball(){
	radius = 0.5;
	stacks = 20;
	splices = 20;
	r = 0.0;
	b = 1.0;
	g = 0.0;
	xSpeed = .05;
	zSpeed = .1;
	this->scale_change(-.85);
	this->translate(0, 1.08, 0);
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
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	glColor3f(r, g, b);
	glutWireSphere(radius, splices ,stacks); // just the use the glut teapot model
	glPopMatrix();
}
