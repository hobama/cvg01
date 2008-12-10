#include <iostream>
#include <vector>
#include "systeminclude.h"
#include "medmath.h"
#include "cordsystem.h"
#include "vertex.h"
#include "objreader.h"
#include "model.h"

using namespace std;

std::vector<float> viewDir(3), viewPos(3);
float fovG=40;
int oldMouseX, oldMouseY;
CordSystem *cordSystem;
Model *model;
//JointBuilder *jointBuilder;
char *characterFile;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//set camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(viewPos[0], viewPos[1], viewPos[2],
			  viewPos[0] + viewDir[0], viewPos[1] + viewDir[1], viewPos[2] + viewDir[2], 
			  0.0, 1.0, 0.0);      /* up is in positive Y direction */
	
	
	float ambient[] = {1.0, 1.0, 1.0, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	
	glPushMatrix();
	cordSystem->draw();
	
	float color[] = {1.0f, 1.0f, 0.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	//static double oldTime=glutGet(GLUT_ELAPSED_TIME);
//	double time=glutGet(GLUT_ELAPSED_TIME);
//	if ((time - oldTime) > 100.0) {
//		model->nextFrame();
//		oldTime=time;
//	}
	model->draw();
	glPopMatrix();
	glutSwapBuffers();
}
void keyPressed(unsigned char key, int x, int y)
{
	const float motionFactor=0.05;
	std::vector<float> sideDir(3), upVector(3);
	upVector[0]=0; upVector[1]=1; upVector[2]=0;
	sideDir = medMath::crossProduct(viewDir, upVector);
	
	switch (key) {
		case 'x':
			glShadeModel(GL_FLAT);
			break;
		case 'z':
			glShadeModel(GL_SMOOTH);
			break;
		case 'c':
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 'v':
			glPolygonMode(GL_BACK, GL_POINT);
			break;
		case 'b':
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case 'w':
			viewPos[0]+= viewDir[0]*motionFactor;
			viewPos[1]+= viewDir[1]*motionFactor;
			viewPos[2]+= viewDir[2]*motionFactor;
			break;
		case 's':
			viewPos[0]-= viewDir[0]*motionFactor;
			viewPos[1]-= viewDir[1]*motionFactor;
			viewPos[2]-= viewDir[2]*motionFactor;
			break;
		case 'a':
			viewPos[0]-= sideDir[0]*motionFactor;
			viewPos[1]-= sideDir[1]*motionFactor;
			viewPos[2]-= sideDir[2]*motionFactor;
			break;
		case 'd':
			viewPos[0]+= sideDir[0]*motionFactor;
			viewPos[1]+= sideDir[1]*motionFactor;
			viewPos[2]+= sideDir[2]*motionFactor;
			break;
		case 'r': // up
			viewPos[0]+= upVector[0]*motionFactor;
			viewPos[1]+= upVector[1]*motionFactor;
			viewPos[2]+= upVector[2]*motionFactor;
			break;
		case 'f': // down
			viewPos[0]-= upVector[0]*motionFactor;
			viewPos[1]-= upVector[1]*motionFactor;
			viewPos[2]-= upVector[2]*motionFactor;
			break;
		case 'm':
			model->nextFrame();
			break;
		case 'n':
			// change fov heere
			break;
		case 'N':
			// change fov heere
			break;
		case '.':
			glDisable(GL_LIGHT0);
			break;
		case ',':
			glEnable(GL_LIGHT0);
			break;
	}
	glutPostRedisplay();
}


void mousePressed(int button, int state, int x, int y)
{
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state==GLUT_DOWN) {
				oldMouseX=x; oldMouseY=y;
			}
			break;	
	}
}

void mouseMotion(int x, int y)
{	
	std::vector<float> rotMatrix(16);
	std::vector<float> viewDirection(4);
	std::vector<float> newViewDirection(4);
	std::vector<float> strafeDir(3), upVector(3);
	
	upVector[0]=0; upVector[1]=1; upVector[2]=0;
	strafeDir = medMath::crossProduct(viewDir, upVector);
	
	float angleLR=(x-oldMouseX) / 200.0;
	float angleUD=(oldMouseY-y) / 10.0;
	oldMouseX = x; 
	oldMouseY = y;
	
	float newDirX, newDirZ; // necessary for matrix multiplication
	// multiply current view Direction with rotation matrix
	newDirX = cos(angleLR) * viewDir[0] - sin(angleLR) * viewDir[2];
	newDirZ = sin(angleLR) * viewDir[0] + cos(angleLR) * viewDir[2];
	
	// set the new direction
	viewDir[0] = newDirX;  
	viewDir[2] = newDirZ;
	
	viewDirection[0] = viewDir[0];
	viewDirection[1] = viewDir[1];
	viewDirection[2] = viewDir[2];
	viewDirection[3] = 1;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
	glLoadIdentity();
	glRotatef(angleUD, strafeDir[0],strafeDir[1],strafeDir[2]);
	glGetFloatv(GL_MODELVIEW_MATRIX, &rotMatrix[0]);
	glPopMatrix(); 
	
	newViewDirection = medMath::matrixMult(rotMatrix, viewDirection);
	
	viewDir[0] = newViewDirection[0];
	viewDir[1] = newViewDirection[1];
	viewDir[2] = newViewDirection[2];
	
	glutPostRedisplay();
}
void init(int argc, char *argv[]) {
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);	
	
	glClearColor(0,0,0,0);
	
	glEnable(GL_LIGHT0);
	/* Setup the view  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( /* field of view in degree */ fovG,
				   /* aspect ratio */ 1.0,
				   /* Z near */ 0.01, /* Z far */ 180.0);
	
	viewPos[0]=-50;  viewPos[1]=0;  viewPos[2]=0; 
	viewDir[0]=11;  viewDir[1]= -0.5;  viewDir[2]=0.5;  
	
	cordSystem = new CordSystem();
	glPointSize(4.0);
	
	
	/**
	 * Joints
	 */
	char *jointfilename = "/Users/a1gucis/Documents/temp/joint.coord";
	char *bvhFilename = "/Users/a1gucis/Documents/temp/motion2rot.bvh";
	char *meshDirectory = "/Users/a1gucis/Documents/temp/objs/"; //meshDirectory name has to end with either / or \ depending on the OS :)
	
	//#############################
	// test field
	
	model = new Model(jointfilename, bvhFilename, meshDirectory);
	model->createJoints();
//	model->nextFrame();
	
	
	//Vertex *vertex = new Vertex(5.0, 5.0, 0.0);
//	vector<float> *rotationVector = new vector<float>(3);
//	(*rotationVector)[0] = 1.0;
//	(*rotationVector)[1] = 0.0;
//	(*rotationVector)[2] = 0.0;
//	vector<float>* newPos = vertex->rotateVertex(90, rotationVector);
//	cout<<"newPos: "<<(*newPos)[0]<<" "<<(*newPos)[1]<<" "<<(*newPos)[2]<<endl;
	//#############################
	
}
int main (int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitWindowSize(640,480);	
	glutInitWindowSize(800,600);
	
	glutCreateWindow("openGL/glut example");
	
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mousePressed);	
	glutIdleFunc(display);
	
	init(argc, argv);
	
	
	glutMainLoop();
    return 0;
	
}

