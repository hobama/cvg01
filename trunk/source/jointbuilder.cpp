#include <string>
#include "jointbuilder.h"


/**
 * Constructor
 */
JointBuilder::JointBuilder(vector<Joint *> *joints, int numOfJoints, Joint *rootJoint) {
	this->joints = joints;
	this->numOfJoints = numOfJoints;
	this->rootJoint = rootJoint;
	
	//this->rootJoint->debugJoint();
}

void JointBuilder::draw() {
	for (int i=0;i<numOfJoints;i++) {
		(*joints)[i]->draw();
	}
}