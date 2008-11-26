/*
 *  polygon.h
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _POLYGON_H_
#define _POLYGON_H_
#include <vector>
#include <iostream>
#include "vertex.h"
#include "normal.h"
#include "texel.h"
#include "systeminclude.h"
using namespace std; 
class Polygon {
protected:
	float x, y, z;
	int size;
	vector<float> *center; // center coordinates
	vector<Vertex *> *vertices;
	vector<Normal *> *normals;
	vector<Texel *> *texels;
public:
	Polygon(int size);
	int getSize();
	void setTranslation(float x, float y, float z);
	void setRotation(float **rotationMatrix, float x, float y, float z);
	void draw();
	vector<float> *getCenter();
	vector<Vertex *> *getVertices();	
	vector<Normal *> *getNormals();
	vector<Texel *> *getTexels();
};

#endif
