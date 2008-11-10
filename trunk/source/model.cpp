/*
 *  model.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "model.h"

Model::Model(char *jointFileName, char *meshDirectory) {
	JointReader *jntReader = new JointReader(jointFileName);
	jntReader->readData();
	rootJoint = jntReader->getRootJoint();
	
	vector<Joint *> *joints = jntReader->getJoints();
	int numOfJoints = jntReader->getNumOfJoints();
	ObjReader *objreader = new ObjReader();
	char meshFileName[128];
	for (int i=0;i<numOfJoints;i++) {
		strcpy(meshFileName, meshDirectory);
		Joint *joint = (*joints)[i];
		char *jointName = joint->getName();
		strcat(meshFileName, jointName);
		strcat(meshFileName, ".obj");
		objreader->readData(meshFileName);
		
		vector<Polygon3 *> *polygons = objreader->getPolygons();
		int numOfPolygons = objreader->getNumOfPolygons();
		Mesh *mesh = new Mesh(polygons, numOfPolygons);
		joint->setMesh(mesh);
	}
	
}

void Model::draw() {
	rootJoint->draw(true);	
}
