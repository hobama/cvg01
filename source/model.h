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
#include "bvhreader.h"
#include "bvhobject.h"
#include "objreader.h"
#include "jointreader.h"
#include "Joint.h"
class Model{
private:
	vector <BVHObject *> *sequence;
	int numberOfJoints, numberOfBvhObjects;
	int numberOfFrames, currentFrame;
	Joint *rootJoint;
	vector<Joint *> *joints;
	BVHReader *bvhReader;
	JointReader *jntReader;
	int getJointIndex(char *name);
	char *meshDirectory;
public:
	Model(char *jointFileName, char *bvhFileName, char *meshDirectory); //for example /Users/a1gucis/Documents/meshes/
	void createJoints();
	void nextFrame();
	void draw();
};

#endif
