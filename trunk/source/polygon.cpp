/*
 *  polygon.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "polygon.h"

Polygon::Polygon(int size) {
	this->size = size;
	vertices = new vector<Vertex *>(size);
	texels = new vector<Texel *>(size);
	normals = new vector<Normal *>(size);
	
	center = new vector<float>(3); // x y z;
	(*center)[0] = 0.0;
	(*center)[1] = 0.0;
	(*center)[2] = 0.0;
}

int Polygon::getSize() {
	return size;
}
void Polygon::draw(float x, float y, float z) {
	glPushMatrix();
	float color[] = {1.0f, 1.0f, 0.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glBegin(GL_POLYGON);
	for (int i=0;i<size;i++) {
		Vertex *vertex = (*vertices)[i];
		glVertex3f(vertex->getX() + x, vertex->getY() + y, vertex->getZ() + z);
		
		Texel *texel = (*texels)[i];
		if (texel != NULL)
			glTexCoord2f(texel->getX(), texel->getY());
		
		Normal *normal = (*normals)[i];
		glNormal3f(normal->getX(), normal->getY(), normal->getZ());
	}
	glEnd();		
	glPopMatrix();
}

vector<float> *Polygon::getCenter() {
	return this->center;
}
vector<Vertex *> *Polygon::getVertices() {
	return vertices;
}

vector<Texel *> *Polygon::getTexels() {
	return texels;
}

vector<Normal *> *Polygon::getNormals() {
	return normals;
}


