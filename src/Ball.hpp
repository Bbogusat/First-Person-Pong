/*
 *	Name: 
 *	ID: 
 *	Class: CP411
 *	Assignment: 3
 *	Date: 11/2/2013
 *	File: Planet.hpp
 */

#ifndef CBall_H
#define CBall_H

#include <GL/glut.h>
#include "Shape.hpp"

class Ball: public Shape{
	protected:
		GLfloat radius, r ,g, b; //radius, red, green, blue
		GLint splices, stacks;
		GLuint textureID;
		GLUquadric *quad;
	public:
		GLfloat xSpeed, zSpeed, xPosition, zPosition;
		Ball();
		void draw();
		void set_colour(GLfloat, GLfloat, GLfloat);
		void setTextureID(int textureID);
};
#endif


