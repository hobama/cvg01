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

class Mesh{
private:
	vector<Polygon3 *> *polygons;
	int numOfPolygons;
public:
	Mesh(vector<Polygon3 *> *polygons, int numOfPolygons);
	void draw();
	
};



#endif