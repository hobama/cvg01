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
	this->jntReader = new JointReader(jointFileName);
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
		if (objreader->readData(meshFileName)) {
			vector<Polygon3 *> *polygons = objreader->getPolygons();
			int numOfPolygons = objreader->getNumOfPolygons();
			Mesh *mesh = new Mesh(polygons, numOfPolygons);
			mesh->setVertices(objreader->getVertices(), objreader->getNumOfVertices());
			joint->setMesh(mesh);
		}
	}
	
	for (int i=0;i<numOfJoints;i++) {
		Joint *joint = (*joints)[i];

		joint->createMeshConnection();

		if (strcmp(joint->getName(),"left_knee") == 0) {
			vector<float> *rotationVector = new vector<float>(3);
			(*rotationVector)[0] = 1.0;
			(*rotationVector)[1] = 0.0;
			(*rotationVector)[2] = 0.0;
			joint->setRotation(90, rotationVector);
		}
		
	}
}

void Model::rotatePart(char* name, int angle) {
	
	Joint *joint = this->jntReader->findJointByName(name);

	vector<float> *rotationVector = new vector<float>(3);
	(*rotationVector)[0] = 1.0;
	(*rotationVector)[1] = 0.0;
	(*rotationVector)[2] = 0.0;
	joint->setRotation(angle, rotationVector);

}

void Model::draw() {
	rootJoint->draw(true);	
}
