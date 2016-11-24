/*
 */

#include "Ball.hpp"
#include <stdio.h>
using namespace std;

Ball::Ball(){
	radius = 1.0;
	stacks = 20;
	splices = 20;
	r = 1.0;
	b = 1.0;
	g = 1.0;
}

/*
 * Ball constructor
 * Parameters:
 * 	the ball to draw if we want more
 */
Ball::Ball(GLint ball){
	radius = 1.0;
	stacks = 20;
	splices = 20;

	r = 0.0;
	b = 1.0;
	g = 0.0;
	this->scale_change(-.9);
	this->translate(1.0, 0.0, 1.0);

}

/*
 * set_colour
 * a function to set the colour of the ball
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
 * the function that draws the ball
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
