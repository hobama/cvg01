/*
 *  model.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "model.h"

Model::Model(char *jointFileName, char *bvhFileName, char *meshDirectory) {
	this->bvhReader = new BVHReader(bvhFileName);
	bvhReader->readData();
	this->sequence = bvhReader->getSequence();
	this->numberOfFrames = bvhReader->getFrameNumber();
	this->currentFrame = 505; //505
	this->numberOfBvhObjects = bvhReader->getObjectsNumber();
	this->numberOfJoints = 0;	
	this->meshDirectory = meshDirectory;
}
int Model::getJointIndex(char *name) {
	int index = -1;
	for (int i=0;i<this->numberOfJoints;i++) {
		Joint *joint = (*joints)[i];
		if (strcmp(joint->getName(), name) == 0)
			index = i;
	}
	return index;
}

void Model::createJoints() {
	//create joints as bvh objects
	joints = new vector<Joint *>(this->numberOfBvhObjects);
	for (int i=0;i<this->numberOfBvhObjects;i++) {
		BVHObject *bvhObject = (*sequence)[i];
		char *name = bvhObject->getName();
		vector<float> *offset = bvhObject->getOffset();
		Joint *joint = new Joint(name, (*offset)[0], (*offset)[1], (*offset)[2]);
		joint->setRotationSequence(bvhObject->getChannelStructure('r'));
		joint->setFrames(bvhObject->getFrames());
		(*joints)[numberOfJoints++]=joint;
	}
	
	//create connections between joints
	for (int i=0;i<this->numberOfJoints;i++) {
		Joint *joint = (*joints)[i];
		BVHObject *bvhObject = (*sequence)[i];
		vector <BVHObject *> *bvhChildren = bvhObject->getChildren();
		for (int i=0;i<bvhObject->getChildrenNumber();i++) {
			BVHObject *bvhChild = (*bvhChildren)[i];
			int childIndex = getJointIndex(bvhChild->getName());
			if (childIndex != -1) {
				Joint *jointChild = (*joints)[childIndex];
				joint->addChild(jointChild);
				jointChild->setParent(joint);
			}
			else
				cout<<"ERROR: creating joint connections"<<endl;
		}
	}
	
	//calculate true joint coordinates and find rootJoint
	for (int i=0;i<this->numberOfJoints;i++) {
		Joint *joint = (*joints)[i];
		Joint *parent = joint->getParent();
		if (parent != NULL) {
			float x = joint->getX() + parent->getX();
			float y = joint->getY() + parent->getY();
			float z = joint->getZ() + parent->getZ();
			joint->setX(x);
			joint->setY(y);
			joint->setZ(z);
		}else
			this->rootJoint = joint;
	}
	
	//load meshes for each joint
	ObjReader *objreader = new ObjReader();
	char meshFileName[128];
	for (int i=0;i<numberOfJoints;i++) {
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
	
	//	//create connections between meshes
		for (int i=0;i<numberOfJoints;i++) {
			Joint *joint = (*joints)[i];
			joint->createMeshConnection();
		}
	//
	
	
}
void Model::nextFrame() {
	if (currentFrame + 1 < numberOfFrames) {
		currentFrame++;
		//cout<<"FRAME: "<<currentFrame<<endl;
		for (int i=0;i<numberOfJoints;i++) {
			Joint *joint = (*joints)[i];
			joint->updateFrame(currentFrame-1);
		}
	//	rootJoint->addTotalRotation();
//		for (int i=0;i<numberOfJoints;i++) {
//			Joint *joint = (*joints)[i];
//			joint->printTotalRotation(currentFrame);
//		}
		
	}
}

void Model::draw() {
	rootJoint->draw(true);	
}