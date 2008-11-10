/*
 *  mesh.cpp
 *  objloader
 *
 *  Created by a1gucis on 11/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "mesh.h"

Mesh::Mesh(vector<Polygon3 *> *polygons, int numOfPolygons) {
	this->polygons = polygons;
	this->numOfPolygons = numOfPolygons;
}

void Mesh::draw() {
	Polygon3 *polygon;
	for (int i=0;i<numOfPolygons;i++){
		polygon = (*polygons)[i];
		polygon->draw();

	}
}