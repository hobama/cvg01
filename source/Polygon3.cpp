/*
 *  Polygon3.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Polygon3.h"

Polygon3::Polygon3(vector<Vertex *> *vertices, vector<Texel *> *texels, vector<Normal *> *normals) : Polygon(3) {
	this->vertices = vertices;
	this->texels = texels;
	this->normals = normals;
	
	float centerX, centerY, centerZ;
	Vertex *vertex = (*vertices)[0];
	centerX = vertex->getX();
	centerY = vertex->getY();
	centerZ = vertex->getZ();
	for (int i=1;i<vertices->size();i++) {
		vertex = (*vertices)[i];
		centerX += vertex->getX();
		centerX /= 2.0;
		
		centerY += vertex->getY();
		centerY /= 2.0;
		
		centerZ += vertex->getZ();
		centerZ /= 2.0;
	}
	
	vector<float> *cntr = new vector<float>(3);
	(*cntr)[0] = centerX;
	(*cntr)[1] = centerY;
	(*cntr)[2] = centerZ;
	this->center = cntr;
}