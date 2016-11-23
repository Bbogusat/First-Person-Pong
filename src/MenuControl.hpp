#include "glsl/Angel.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "glaux.h" // for reading bmp files

#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "mesh.hpp"
#include "bezier/Bezier.hpp"
#include "solar/Solar.hpp"

#include "pixmap/RGBpixmap.h"

RGBpixmap pix[6];   // make six pixmaps

GLint winWidth = 800, winHeight = 800;
GLfloat red = 1.0, green = 1.0, blue = 1.0;
GLint moving = 0, xBegin = 0, coordinate = 1, type = 4, selected = 0, solarAnimation = 0, Ptgen = 1, BCgen = 0, BCRotation = 0;
bool isShading = false;
bool isTexture = false;
bool isSolar = false;

//Declare a world containing all objects
World myWorld;
Camera myCamera;
Light myLight;
Solar mySolar;
Bezier myBezier;
Cube* myCube = (Cube*) myWorld.list[0];


//declare shader program object
GLuint ProgramObject;
GLuint theta;

// light properties
GLfloat ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat diffuse[] = { .6f, .6f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat local_view[] = { 0.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

//function prototypes
void reset(void);
void close(void);
void move(); // cube
void animate_solar(int); // solar system

void MCTransMenu(GLint transOption) {
	coordinate = 1;
	type = transOption;
	glutPostRedisplay();
}

void WCTransMenu(GLint transOption) {
	coordinate = 2;
	type = transOption;
	glutPostRedisplay();
}

void VCTransMenu(GLint transOption) {
	coordinate = 3;
	type = transOption;
	glutPostRedisplay();
}

void LightMenu(GLint transOption) {
	coordinate = 4;
	type = transOption;

	if (type == 10) {
		myLight.On = true;
	}
	if (type == 11) {
		myLight.On = false;
	}
	glutPostRedisplay();
}

void mainMenu(GLint option) {
	switch(option) {
	case 1:
		reset();
		break;
	case 2:
		close();
		break;
	}
	glutPostRedisplay();
}

void colorSubMenu(GLint colorOption) {
	switch(colorOption) {
	case 1:
		red = 1.0; green = 0.0; blue = 0.0;
		break;
	case 2:
		red = 0.0; green = 1.0; blue = 0.0;
		break;
	case 3:
		red = 0.0; green = 0.0; blue = 1.0;
		break;
	}
	glutPostRedisplay();
}

void ObjSubMenu(GLint objectOption) {
	selected = objectOption;
	glutPostRedisplay();
}

void A3Menu(GLint option) {
	selected = 0;
	Ptgen = 0;
	BCgen = 0;
	BCRotation = 0;
	isTexture = false;
	glUseProgram(0);
	glutIdleFunc(NULL);
	solarAnimation = 0;
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);

	isSolar = false;

	if(option == 1){ // my backface
		isShading = false;
		glDisable( GL_LIGHTING );
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

	} else if(option == 2){
		isShading = true;
		glDisable( GL_LIGHTING );
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

	} else if(option == 3){
		isShading = false;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

	}

	else if(option == 4){ //cube animation

		selected = 0;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		glDisable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glutIdleFunc(move);
	}

	else if(option == 5){ //solar system
//		isSolar = true;
//		myLight.On = false;
//		glDisable( GL_LIGHTING );
//		glutIdleFunc(move);
//

		selected = 1;
		solarAnimation = 1;
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);

		// Set up simple lighting model
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glEnable( GL_TEXTURE_2D);
		animate_solar(1);

	}

	 else if (option == 6){
			isShading = false;
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);

			 glEnable(GL_NORMALIZE);
			// Light model parameters:
			 // -------------------------------------------

			 GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
			 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
			 glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
			 glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

			 // -------------------------------------------
			 // Spotlight Attenuation

			 GLfloat spot_direction[] = {4.0, 4.0, 4.0 };
			 GLint spot_exponent = 30;
			 GLint spot_cutoff = 180;

			 glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
			 glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
			 glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

			 GLfloat Kc = 1.0;
			 GLfloat Kl = 0.0;
			 GLfloat Kq = 0.0;

			 glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
			 glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
			 glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


			 // -------------------------------------------
		     // Lighting parameters:

			 GLfloat light_pos[] = {myLight.getMC().mat[0][3], myLight.getMC().mat[1][3], myLight.getMC().mat[2][3], 1.0f};
			 GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
			 GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
			 GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

			 glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
			 glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
			 glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
			 glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

			 // -------------------------------------------
			 // Material parameters:
			 GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
			 GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
			 GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
			 GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
			 GLfloat material_Se = 20.0f;

			 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
			 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
			 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
			 glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
			 glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		}

	glutPostRedisplay();

}

void A4Menu(GLint option) {
	selected = 2;
	Ptgen = 0;
	BCgen = 0;
	BCRotation = 0;
	isTexture = false;
	glUseProgram(0);
	glutIdleFunc(NULL);
	solarAnimation = 0;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	switch (option) {
		case 1: Ptgen = 1; glFlush(); glutPostRedisplay(); break;
		case 2: BCgen = 1; break;
		case 3:
			selected = 2;
			BCRotation = 1;
			myBezier.RotateBezier(myBezier.ctrlPts, myBezier.nCtrlPts, myBezier.T);
			break;

		case 4:
			selected = 2;
			BCRotation = 1;
			glUseProgram(0);
			myBezier.setRenderMode(myBezier.MODE_WIRE);

			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			glDisable(GL_LIGHTING);
			glDisable(GL_NORMALIZE);
			glDisable(GL_COLOR_MATERIAL);
			glDisable(GL_LIGHT0);
			break;

		case 5:
			selected = 2;
			BCRotation = 1;
			glUseProgram(0);
			myBezier.setRenderMode(myBezier.MODE_SOLID);


			glEnable(GL_DEPTH_TEST); // enable OpenGL depth buffer algorithm for hidden surface removal
			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);
			glEnable( GL_NORMALIZE);
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_LIGHT0);
			glCullFace(GL_BACK);
			break;

		case 6:
			selected = 2;
			BCRotation = 1;

			glUseProgram( ProgramObject );
			myBezier.setRenderMode(myBezier.MODE_SOLID);

			myLight.On = true;
			myLight.draw();

			position[0] = myLight.getMC().mat[0][3];
			position[1] = myLight.getMC().mat[1][3];
			position[2] = myLight.getMC().mat[2][3];

			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_POSITION, position);

			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
			glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
			glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

			glEnable(GL_DEPTH_TEST); // enable OpenGL depth buffer algorithm for hidden surface removal
			glEnable(GL_CULL_FACE);
			glEnable(GL_LIGHTING);
			glEnable( GL_NORMALIZE);
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_LIGHT0);
			glCullFace(GL_BACK);

			break;

		case 7:
			glUseProgram(0);
			selected = 0;
			isTexture = true;
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			break;

		case 8:
			glUseProgram(0);
			selected = 1;
			solarAnimation = 1;

			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);


			animate_solar(1);
			break;

		default: break;

	}

	glutPostRedisplay();
}

void RotationMenu(GLint option) {
	switch (option) {
		case 1: myBezier.R = 45; break;
		case 2: myBezier.R = 90; break;
		case 3: myBezier.R = 135; break;
		case 4: myBezier.R = 180; break;
		case 5: myBezier.R = 225; break;
		case 6: myBezier.R = 270; break;
		case 7: myBezier.R = 315; break;
		case 8: myBezier.R = 360; break;
		case 9: myBezier.S = 5; break;
		case 10: myBezier.S = 10; break;
		case 11: myBezier.S = 15; break;
		case 12: myBezier.T = 5; break;
		case 13: myBezier.T = 10; break;
		case 14: myBezier.T = 15; break;
		case 15: myBezier.T = 20; break;
		case 16: myBezier.T = 25; break;
		default: break;
	}
	myBezier.RotateBezier(myBezier.ctrlPts, myBezier.nCtrlPts, myBezier.T);
	glutPostRedisplay();
}

void menu() {
	GLint MCTrans_Menu = glutCreateMenu(MCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Scale", 4);

	GLint WCTrans_Menu = glutCreateMenu(WCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);

	GLint VCTrans_Menu = glutCreateMenu(VCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Clipping Near ", 7);
	glutAddMenuEntry(" Clipping Far ", 8);
	glutAddMenuEntry(" Angle ", 9);

	GLint Light_Menu = glutCreateMenu(LightMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Translate x ", 4);
	glutAddMenuEntry(" Translate y ", 5);
	glutAddMenuEntry(" Translate z", 6);
	glutAddMenuEntry(" Point Light Intensity I", 7);
	glutAddMenuEntry(" Point Light Reflection Rd", 8);
	glutAddMenuEntry(" Ambient Reflection Ra",9);
	glutAddMenuEntry(" Show Point Light ", 10);
	glutAddMenuEntry(" Hide Point Light ", 11);

	//A_3 menu
	GLint A3_Menu = glutCreateMenu(A3Menu);
	glutAddMenuEntry(" My Hidden Face Removal", 1);
	glutAddMenuEntry(" My Light & Shading ", 2);
	glutAddMenuEntry(" OpenGL Hidden Face Removal", 3);
	glutAddMenuEntry(" OpenGL Light & Shading", 6);
	glutAddMenuEntry(" Cube Animation ", 4);
	glutAddMenuEntry(" Simple Solar System", 5);

	GLint Rotation_Menu = glutCreateMenu(RotationMenu);
	glutAddMenuEntry(" R->45 ", 1);
	glutAddMenuEntry(" R->90 ", 2);
	glutAddMenuEntry(" R->135 ", 3);
	glutAddMenuEntry(" R->180 ", 4);
	glutAddMenuEntry(" R->225 ", 5);
	glutAddMenuEntry(" R->270 ", 6);
	glutAddMenuEntry(" R->315 ", 7);
	glutAddMenuEntry(" R->360 ", 8);
	glutAddMenuEntry(" S->5 ", 9);
	glutAddMenuEntry(" S->10 ", 10);
	glutAddMenuEntry(" S->15 ", 11);
	glutAddMenuEntry(" T->5 ", 12);
	glutAddMenuEntry(" T->10 ", 13);
	glutAddMenuEntry(" T->15 ", 14);
	glutAddMenuEntry(" T->20 ", 15);
	glutAddMenuEntry(" T->25 ", 16);

	//A_4 menu
	GLint A4_Menu = glutCreateMenu(A4Menu);
	glutAddMenuEntry(" Control Point Selection ", 1);
	glutAddMenuEntry(" Bezier Curve Generation ", 2);
	glutAddSubMenu(" Rotation Configuration ", Rotation_Menu);
	glutAddMenuEntry(" Rotation surface Generation ", 3);
	glutAddMenuEntry(" Wired Mesh ", 4);
	glutAddMenuEntry(" Solid Mesh OpenGL Shading ", 5);
	glutAddMenuEntry(" Solid Mesh GLSL Shading ", 6);
	glutAddMenuEntry(" Cube Texture ",7);
	glutAddMenuEntry(" Solar System Texture ", 8);

	// main menu
	glutCreateMenu(mainMenu);
	glutAddMenuEntry(" Reset ", 1);
	glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations ", Light_Menu);
	glutAddSubMenu(" A3 Menu ", A3_Menu);
	glutAddSubMenu(" A4 Menu ", A4_Menu);
	glutAddMenuEntry(" Quit ", 2);
}
