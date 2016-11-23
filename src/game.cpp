/**
 *	CP411 Assignment 4
 *	Ben Bogusat
 */

#include "MenuControl.hpp"

void init(void) {
	myLight.translate(1.5, 1.5, 1.5);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Smooth out lines
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);

	//load and set vertex and fragement shader
	ProgramObject = InitShader("vertexshader.txt","fragmentshader.txt");
	glUseProgram(0);

	// load and and set texture
	pix[0].makeCheckerboard();
	pix[0].setTexture(0);

	pix[1].readBMPFile("mandrill.bmp");
	pix[1].setTexture(1);

	pix[2].readBMPFile("sun.bmp");
	pix[2].setTexture(2);

	pix[3].readBMPFile("earth.bmp");
	pix[3].setTexture(3);

	pix[4].readBMPFile("moon.bmp");
	pix[4].setTexture(4);

	pix[5].readBMPFile("draw.bmp");
	pix[5].setTexture(5);

    // load other textures

	//set textureID for cube

	myCube->setTextureID(0, 0);
	myCube->setTextureID(0, 0);
	myCube->setTextureID(1, 1);
	myCube->setTextureID(1, 1);
	myCube->setTextureID(2, 2);
	myCube->setTextureID(3, 3);
	myCube->setTextureID(4, 4);
	myCube->setTextureID(5, 5);

	//set texture for Solar system
	mySolar.Earth->textureID = 3;
	mySolar.Sun->textureID = 2;
	mySolar.Moon->textureID = 4;

	// register objects world, so that transfermations can be applied to the objects
    myWorld.list[1] = &mySolar;
    myWorld.list[2] = &myBezier;
}


void reset(void) {
	glutIdleFunc(NULL);
	glUseProgram(0);
	selected = 2;
	Ptgen = 1;
	BCgen = 0;
	BCRotation = 0;
	solarAnimation = 0;
	isSolar = false;
	isShading = false;
	isTexture = false;
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable( GL_LIGHTING );
	glDisable(GL_LIGHT0);
	myWorld.reset();
	myBezier.reset();
	glFlush();
	glutPostRedisplay();
}

void close(void) {
	exit(1);
}

void display(void) {
	if (Ptgen == 1) {
		myBezier.displayCPts();
		glFlush();
	}

	else if (BCgen == 1) {
		myBezier.displayBezCurve();
	}

	else if (BCRotation == 1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix();  // change to 3D view

        // draw the coordinate frames
		glLineWidth(3);
		glBegin(GL_LINES);
		//x-axis
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(2, 0, 0);
		glVertex3f(0, 0, 0);
		//y-axis
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0, 2, 0);
		glVertex3f(0, 0, 0);
		//z-axis
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 0, 2);
		glVertex3f(0, 0, 0);
		glEnd();
		glLineWidth(1);

		myLight.draw();
		myBezier.draw();
	}

	else if (solarAnimation == 1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix();
		mySolar.draw();
	}

	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myCamera.setProjectionMatrix();
		myWorld.draw_world(); // draw all objects in the world
		myLight.draw();
	}

	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		xBegin = x;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Ptgen == 1) {
		myBezier.ctrlPts[myBezier.nCtrlPts].x = x - winWidth / 2;
		myBezier.ctrlPts[myBezier.nCtrlPts].y = winHeight / 2 - y;
		myBezier.ctrlPts[myBezier.nCtrlPts].z = 0;

		printf("Point %d set: %f %f \n", myBezier.nCtrlPts, myBezier.ctrlPts[myBezier.nCtrlPts].x, myBezier.ctrlPts[myBezier.nCtrlPts].z);

		if ( myBezier.nCtrlPts < 10) {
			 myBezier.nCtrlPts++;
		}
	}
	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;

	if (moving) {
		if (coordinate == 1) {
			if (type == 1) {
				theta = (xBegin - x > 0) ? 1 : -1;
				rx = myWorld.list[selected]->getMC().mat[0][0];
				ry = myWorld.list[selected]->getMC().mat[1][0];
				rz = myWorld.list[selected]->getMC().mat[2][0];
				myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 1);
			}
			else if (type == 2) {
				theta = (xBegin - x > 0) ? 1 : -1;
				rx = myWorld.list[selected]->getMC().mat[0][1];
				ry = myWorld.list[selected]->getMC().mat[1][1];
				rz = myWorld.list[selected]->getMC().mat[2][1];
				myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 1);
			}
			else if (type == 3) {
				theta = (xBegin - x > 0) ? 1 : -1;
				rx = myWorld.list[selected]->getMC().mat[0][2];
				ry = myWorld.list[selected]->getMC().mat[1][2];
				rz = myWorld.list[selected]->getMC().mat[2][2];
				myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 1);
			}

			else if (type == 4) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myWorld.list[selected]->scale_change(theta * 0.02);
			}
		}

		else if (coordinate == 2) {
			if ( type == 1) {
				theta = (xBegin - x > 0) ? 1 : -1;
				myWorld.list[selected]->rotate_origin(1, 0, 0, theta * 0.5);
			}

			else if (type == 2) {
				theta = (xBegin - x > 0) ? 1 : -1;
				myWorld.list[selected]->rotate_origin(0, 1, 0, theta * 0.5);
			}

			else if (type == 3) {
				theta = (xBegin - x > 0) ? 1 : -1;
				myWorld.list[selected]->rotate_origin(0, 0, 1, theta * 0.5);
			}

			else if (type == 4) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myWorld.list[selected]->translate(theta * 0.02, 0, 0);
			}

			else if (type == 5) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myWorld.list[selected]->translate(0, theta * 0.02, 0);
			}

			else if (type == 6) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myWorld.list[selected]->translate(0, 0, theta * 0.02);
			}

		}

		else if (coordinate == 3 ) {

			if (type == 1) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myCamera.rotate(1.0, 0.0, 0.0, theta*0.5);
			}

			else if (type == 2) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myCamera.rotate(0.0, 1.0, 0.0, theta*0.5);
			}

			else if (type == 3) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myCamera.rotate(0.0, 0.0, 1.0, theta*0.5);
			}

			else if (type == 4) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myCamera.translate(theta*0.5, 0.0, 0.0);
			}

			else if (type == 5) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myCamera.translate(0.0, theta*0.5, 0.0);
			}

			else if (type == 5) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myCamera.translate(0.0, 0.0, theta*0.5);
			}
		}

		else if (coordinate == 4 ) {

			if (type == 1) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.rotate_origin(1, 0, 0, theta * 0.5);

			}

			else if (type == 2) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.rotate_origin(0.0, 1.0, 0.0, theta*0.5);
			}

			else if (type == 3) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.rotate_origin(0.0, 0.0, 1.0, theta*0.5);
			}

			else if (type == 4) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.translate(theta*0.02, 0.0, 0.0);
			}

			else if (type == 5) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.translate(0.0, theta*0.02, 0.0);
			}

			else if (type == 6) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.translate(0.0, 0.0, theta*0.02);
			}

			else if (type == 7) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.Increment(theta*0.02,0, 0);
			}

			else if (type == 8) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.Increment(0, 0, theta*0.02);

			}
			else if (type == 9) {
				theta = (xBegin - x < 0) ? 1 : -1;
				myLight.Increment(0, theta*0.02, 0);
			}


			position[0] = myLight.getMC().mat[0][3];
			position[1] = myLight.getMC().mat[1][3];
			position[2] = myLight.getMC().mat[2][3];
			glLightfv(GL_LIGHT0, GL_POSITION, position);

		}
	}
	glutPostRedisplay();
}

void move(void){
	GLfloat rx,ry,rz;
	if (moving == 0){
		if(!isSolar) {
			rx = myWorld.list[selected]->getMC().mat[0][1];
			ry = myWorld.list[selected]->getMC().mat[1][1];
			rz = myWorld.list[selected]->getMC().mat[2][1];
			myWorld.list[selected]->rotate_mc(rx, ry, rz, 0.1);
		}
		glutPostRedisplay();
	}
}

void animate_solar(int keepGoing) {
      mySolar.Sun->rotate_mc(0, -1, 0, 2);

      mySolar.Earth->rotate_mc(mySolar.Earth->getMC().mat[0][0], mySolar.Earth->getMC().mat[1][0], mySolar.Earth->getMC().mat[2][0], 3);
      mySolar.Earth->rotate_relative(mySolar.Sun->getMC().mat[0][3], mySolar.Sun->getMC().mat[1][3],  mySolar.Sun->getMC().mat[2][3], 0, -1, 0, 4);

      mySolar.Moon->rotate_mc(mySolar.Moon->getMC().mat[0][0], mySolar.Moon->getMC().mat[1][0], mySolar.Moon->getMC().mat[2][0], 4);
      mySolar.Moon->rotate_relative(mySolar.Sun->getMC().mat[0][3], mySolar.Sun->getMC().mat[1][3],  mySolar.Sun->getMC().mat[2][3], 0, -1, 0, 4);
      mySolar.Moon->rotate_relative(mySolar.Earth->getMC().mat[0][3], mySolar.Earth->getMC().mat[1][3], mySolar.Earth->getMC().mat[2][3],  0, -1, 0, 6);

     if (keepGoing && solarAnimation == 1) {
    	  glutTimerFunc(40, animate_solar, 1);  // callback every 40 ms
      }
      glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("CP411 A4 (by Ben Bogusat)");
	glewInit(); // for using GSLS

	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

