/*
 *  model.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "model.h"

Model::Model(char *bvhFileName, char *meshDirectory) {
	//create joints
	//this->jntReader = new JointReader(jointFileName);
//	jntReader->readData();
//	rootJoint = jntReader->getRootJoint();
	this->bvhReader = new BVHReader(bvhFileName);
	bvhReader->readData();
	this->rootBVHObject = bvhReader->getRootBVHObject();
	this->sequence = bvhReader->getSequence();
	this->numberOfFrames = bvhReader->getFrameNumber();
	this->currentFrame = 0;
	this->numberOfBvhObjects = bvhReader->getObjectsNumber();
	this->numberOfJoints = 0;
	//cout<<"bvh Objects number: "<<bvhReader->getObjectsNumber()<<endl;
	//load meshes
	//vector<Joint *> *joints = jntReader->getJoints();
//	int numOfJoints = jntReader->getNumOfJoints();
//	ObjReader *objreader = new ObjReader();
//	char meshFileName[128];
//	for (int i=0;i<numOfJoints;i++) {
//		strcpy(meshFileName, meshDirectory);
//		Joint *joint = (*joints)[i];
//		char *jointName = joint->getName();
//		strcat(meshFileName, jointName);
//		strcat(meshFileName, ".obj");
//		if (objreader->readData(meshFileName)) {
//			vector<Polygon3 *> *polygons = objreader->getPolygons();
//			int numOfPolygons = objreader->getNumOfPolygons();
//			Mesh *mesh = new Mesh(polygons, numOfPolygons);
//			mesh->setVertices(objreader->getVertices(), objreader->getNumOfVertices());
//			joint->setMesh(mesh);
//		}
//	}
//	
	//create connections between meshes
	//for (int i=0;i<numOfJoints;i++) {
//		Joint *joint = (*joints)[i];
//		joint->createMeshConnection();
//	}
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
				cout<<joint->getName()<<"->"<<jointChild->getName()<<endl;
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
			float originalX = joint->getOriginalX() + parent->getOriginalX();
			float originalY = joint->getOriginalY() + parent->getOriginalY();
			float originalZ = joint->getOriginalZ() + parent->getOriginalZ();
			joint->setOriginalXYZ(originalX, originalY, originalZ);
		}else
			this->rootJoint = joint;
	}

}
void Model::rotatePart(char* name, float angle, vector<float> *rotationVector) {
	
	//Joint *joint = this->jntReader->findJointByName(name);
	//joint->setRotation(angle, rotationVector);

}

void Model::translatePart(char *name, float x, float y, float z) {
	//Joint *joint = this->jntReader->findJointByName(name);
	//joint->setTranslation(x, y, z);
	//joint->setRotation(angle, rotationVector);
}

void Model::nextFrame() {
	if (currentFrame + 1 < numberOfFrames) {
		currentFrame++;
		//cout<<"FRAME: "<<currentFrame<<endl;
		for (int i=0;i<numberOfJoints;i++) {
			Joint *joint = (*joints)[i];
			//cout<<"Animating: "<<joint->getName()<<endl;
			joint->updateFrame(currentFrame);
		}
	}
}
void Model::draw() {
	rootJoint->draw(true);	
}
