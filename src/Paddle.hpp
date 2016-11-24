#ifndef CPaddle_H
#define CPaddle_H

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Shape.hpp"


class Paddle: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];      	 // face color
	GLfloat paddle_face_norm_mc[6][3]; // normal face in mc
	GLfloat paddle_face_norm_wc[6][4]; // normal face in wc
	GLuint textureID[6];             // face textureID for face i

public:
	Paddle();
	void draw_face(int);
	void draw();
	bool isBackface(int);
	GLfloat getFaceShade(int);
	void setTextureID(int index, int textureid);
};

#endif
