/*
 *  mesh.h
 *  objloader
 *
 *  Created by a1gucis on 11/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _MESH_H_
#define _MESH_H_
#include <vector>
#include <iostream>
#include "systeminclude.h"
#include "Polygon3.h"
#include "vertex.h"
class Mesh{
private:
	float x, y, z;
	vector<Polygon3 *> *polygons;
	vector<Vertex *> *vertices;
	int numOfPolygons, numOfVertices;
public:
	Mesh(vector<Polygon3 *> *polygons, int numOfPolygons);
	void setVertices(vector<Vertex *> *vertices, int numOfVertices);
	vector<Vertex *> *getVertices();
	int getNumOfVertices();
	void addTranslation(float x, float y, float z);
	void draw();
	
};



#endif