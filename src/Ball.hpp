/*
 */

#ifndef CBall_H
#define CBall_H

#include <GL/glut.h>
#include "Shape.hpp"

class Ball: public Shape{
	protected:
		GLfloat radius, r ,g, b; //radius, red, green, blue
		GLint splices, stacks;
	public:
		Ball();
		Ball(GLint);
		void draw();
		void set_colour(GLfloat, GLfloat, GLfloat);

};
#endif


