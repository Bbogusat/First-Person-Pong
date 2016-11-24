/*
 */

#ifndef CBall_H
#define CBall_H

#include <GL/glut.h>
#include "Shape.hpp"

class Ball: public Shape{
	protected:
		GLfloat radius, r ,g, b, xSpeed, zSpeed; //radius, red, green, blue, xSpeed, zSpeed
		GLint splices, stacks;
	public:
		Ball();
		void draw();
		void set_colour(GLfloat, GLfloat, GLfloat);

};
#endif


