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
#include <string>
#include "Polygon3.h"
#include "jointreader.h"
#include "bvhreader.h"
#include "Joint.h"
class Model{
private:
	BVHObject *rootBVHObject;
	vector <BVHObject *> *sequence;
	int numberOfJoints, numberOfBvhObjects;
	int numberOfFrames, currentFrame;
	Joint *rootJoint;
	vector<Joint *> *joints;
	BVHReader *bvhReader;
	
	int getJointIndex(char *name);
public:
	Model(char *bvhFileName, char *meshDirectory); //for example /Users/a1gucis/Documents/meshes/
	void createJoints();
	void rotatePart(char* name, float angle, vector<float> *rotationVector);
	void translatePart(char *name, float x, float y, float z);
	void nextFrame();
	void draw();
};

#endif
