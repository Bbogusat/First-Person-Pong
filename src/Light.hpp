/*
 *	Name: 
 *	ID: 
 *	Class: CP411
 *	Assignment: 3
 *	Date: 10/24/2013
 *	File: Light.hpp
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_
#include <GL/glut.h>
#include "Shape.hpp"

extern GLfloat light0_ambient[];
extern GLfloat light0_diffuse[];
extern GLfloat light0_position[];

class Light : public Shape {
	public:
		//light and shading. use MC origin as the light position
		GLfloat I, Rd, Ia, Ra;
		GLboolean On;
		GLfloat Size;

		Light();
		void Reset();
		void draw();
		void LightReset();
		void Increment(GLfloat, GLfloat, GLfloat);

};
#endif /* LIGHT_HPP_ */
