/*
 * Table.hpp
 *
 *  Created on: Nov 24, 2016
 */

#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Shape.hpp"
#include "Leg.hpp"


class Table: public Shape {
	GLuint textureID[6];             // face textureID for surfaces
	Leg* frontRightLeg;
	Leg* backLeftLeg;
	Leg* backRightLeg;
	Leg* frontLeftLeg;

public:
	Table();
	void draw_table();
	void setTextureID(int index, int textureid);
};

#endif
