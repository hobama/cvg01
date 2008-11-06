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
}

int Polygon::getSize() {
	return size;
}
void Polygon::draw() {
	//glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i=0;i<size;i++) {
		Vertex *vertex = (*vertices)[i];
		glVertex3f(vertex->getX(), vertex->getY(), vertex->getZ());
		
		Texel *texel = (*texels)[i];
		if (texel != NULL)
			glTexCoord2f(texel->getX(), texel->getY());
		
		Normal *normal = (*normals)[i];
		glNormal3f(normal->getX(), normal->getY(), normal->getZ());
	}
	glEnd();		
	//glPopMatrix();
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


