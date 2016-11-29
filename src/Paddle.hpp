#ifndef CPaddle_H
#define CPaddle_H

#include <vector>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Shape.hpp"
#include "Point.hpp"



class Paddle: public Shape {
protected:
	GLint player;
	GLfloat xPosition, zPosition;
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];      	 // face color
	GLfloat paddle_face_norm_mc[6][3]; // normal face in mc
	GLfloat paddle_face_norm_wc[6][4]; // normal face in wc
	GLuint textureID[6];             // face textureID for face i


public:
	Paddle();
	Paddle(int playernum);
	void draw_face(int);
	void draw();
	void translate(GLfloat tx, GLfloat ty, GLfloat tz);
	bool isBackface(int);
	GLfloat getFaceShade(int);
	std::vector<Point> getBounds();
	void setTextureID(int index, int textureid);

};

#endif
