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
#include "systeminclude.h"
#include <vector>
#include <iostream>
#include "vertex.h"
#include "normal.h"
#include "texel.h"
using namespace std; 
class Polygon {
protected:
	int size;
	vector<Vertex *> *vertices;
	vector<Normal *> *normals;
	vector<Texel *> *texels;
public:
	Polygon(int size);
	int getSize();
	void draw();
	vector<Vertex *> *getVertices();	
	vector<Normal *> *getNormals();
	vector<Texel *> *getTexels();
};

#endif