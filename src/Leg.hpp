/*
 * Leg.hpp
 *
 *  Created on: Nov 24, 2016
 *      Author: Ben
 */

#ifndef LEG_HPP_
#define LEG_HPP_

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Shape.hpp"


class Leg: public Shape {

private:
	GLuint textureID;             // face textureID for surfaces
	GLfloat vertex[8][3];
	GLint face[4][4];
	GLfloat x,y,z,x2,y2,z2;

public:
	Leg();
	Leg(GLfloat x, GLfloat y, GLfloat z);
	void draw_face(int i);
	void draw_leg();
	void setTextureID(int textureid);
};

#endif
