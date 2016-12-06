/*
 * Leg.cpp
 * Author: Benjamin Bogusat
 */

#include "Leg.hpp"

Leg::Leg(){
	textureID=0;
}
Leg::Leg(GLfloat x, GLfloat y, GLfloat z) {
	// x=1, y=.5, z=1.8
	this->x = x;
	this->y = y;
	this->z = z;
	this->x2 = GLfloat(x) - GLfloat(0.2);
	this->y2 = GLfloat(y) - GLfloat(1.5);
	this->z2 = GLfloat(z) + GLfloat(.2);

	//Back Face
	vertex[0][0] = this->x2;vertex[0][1] = this->y2; vertex[0][2] = this->z;
	vertex[1][0] = this->x2;vertex[1][1] = this->y;vertex[1][2] = this->z;
	vertex[2][0] = this->x;vertex[2][1] = this->y;vertex[2][2] = this->z;
	vertex[3][0] = this->x;vertex[3][1] = this->y2; vertex[3][2] = this->z;

	//Left Side
	vertex[4][0] = this->x2;vertex[4][1] = this->y2;vertex[4][2] = this->z2;
	vertex[5][0] = this->x2;vertex[5][1] = this->y;vertex[5][2] = this->z2;
	//Vertex [3]
	//Vertex [2]

	//Right Side
	vertex[6][0] = this->x;vertex[6][1] = this->y;vertex[6][2] = this->z2;
	vertex[7][0] = this->x;vertex[7][1] = this->y2;vertex[7][2] = this->z2;
	//Vertex [1]
	//Vertex [0]

	//Front Face
	//Vertex [6]
	//Vertex [7]
	//Vertex [4]
	//Vertex [5]


	face[0][0] = 0;face[0][1] = 1;face[0][2] = 2;face[0][3] = 3;
	face[1][0] = 4;face[1][1] = 5;face[1][2] = 1;face[1][3] = 0;
	face[2][0] = 7;face[2][1] = 6;face[2][2] = 2;face[2][3] = 3;
	face[3][0] = 4;face[3][1] = 5;face[3][2] = 6;face[3][3] = 7;


	textureID = 0;

}

void Leg::draw_face(int i) {
	glBindTexture(GL_TEXTURE_2D, textureID);
			glBegin(GL_QUADS);
				glTexCoord2d(0.0,0.0);
				glVertex3fv(&vertex[face[i][0]][0]);
				glTexCoord2d(1.0,0.0);
				glVertex3fv(&vertex[face[i][1]][0]);
				glTexCoord2d(1.0,1.0);
				glVertex3fv(&vertex[face[i][2]][0]);
				glTexCoord2d(0.0,1.0);
				glVertex3fv(&vertex[face[i][3]][0]);
			glEnd();

}

void Leg::draw_leg()
{
	for (int i = 0; i < 4; i++) {
    		draw_face(i);
    		if(i == 0){
    		}
    }
}

void Leg::setTextureID(int textureid) {
	textureID = textureid;
}
