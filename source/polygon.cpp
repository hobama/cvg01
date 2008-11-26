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
	
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

void Polygon::setTranslation(float x, float y, float z) {
	for (int i=0;i<size;i++) {
		Vertex *vertex = (*vertices)[i];
		vertex->setX(x);
		vertex->setY(y);
		vertex->setZ(z);
	}
	
}
void Polygon::setRotation(float **rotationMatrix, float x, float y, float z) {
	for (int i=0;i<size;i++) {
		Vertex *vertex = (*vertices)[i];
		vertex->setRotation(rotationMatrix, x, y, z);
	}
}
int Polygon::getSize() {
	return size;
}
void Polygon::draw() {
	glPushMatrix();
	float color[] = {1.0f, 1.0f, 0.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glBegin(GL_POLYGON);
	for (int i=0;i<size;i++) {
		Vertex *vertex = (*vertices)[i];
		glVertex3f(vertex->getX() + vertex->getOriginalX(), vertex->getY() + vertex->getOriginalY(), vertex->getZ() + vertex->getOriginalZ());
		
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


