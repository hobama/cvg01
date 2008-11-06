/*
 *  cordSystem.cpp
 *  animation
 *
 *  Created by a1gucis on 10/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "cordsystem.h"

void CordSystem::draw() {
	glPushMatrix();
	float color[] = {1.0f, 0.0f, 0.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glBegin(GL_LINES); //x - axis
	glVertex3f(-1000.0, 0.0, 0.0);
	glVertex3f(1000.0, 0.0, 0.0);
	glEnd();
	
	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glBegin(GL_LINES); //y - axis
	glVertex3f(0.0, -1000.0, 0.0);
	glVertex3f(0.0, 1000.0, 0.0);
	glEnd();
	
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glBegin(GL_LINES); //z - axis
	glVertex3f(0.0, 0.0, -1000.0);
	glVertex3f(0.0, 0.0, 1000.0);
	glEnd();
	glPopMatrix();
}