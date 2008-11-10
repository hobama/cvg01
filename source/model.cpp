/*
 *  model.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "model.h"

Model::Model(vector<Polygon3 *> *polygons, int numOfPolygons, JointBuilder *jointBuilder) {
	this->polygons = polygons;
	this->numOfPolygons = numOfPolygons;
	this->jointBuilder = jointBuilder;
	cout <<"numOfpolygons: "<<numOfPolygons<<endl;
}

void Model::draw() {
	Polygon3 *polygon;
	for (int i=0;i<numOfPolygons;i++) {
		polygon = (*polygons)[i];
		polygon->draw();
	}

	// Draw joints
	jointBuilder->draw();
	
}
