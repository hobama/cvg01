/*
 *  model.h
 *  objloader
 *
 *  Created by a1gucis on 10/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include "Polygon3.h"
#include "jointbuilder.h"
class Model{
private:
	int numOfPolygons;
	vector<Polygon3 *> *polygons;
	JointBuilder *jointBuilder;
public:
	Model(vector<Polygon3 *> *polygons, int numOfPolygons, JointBuilder *jointBuilder);
	void draw();
};

#endif
