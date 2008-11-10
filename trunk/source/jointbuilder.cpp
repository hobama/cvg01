#include <string>
#include "jointbuilder.h"


/**
 * Constructor
 */
JointBuilder::JointBuilder(vector<Joint *> *joints, int numOfJoints) {
	this->joints = joints;
	this->numOfJoints = numOfJoints;
}

void JointBuilder::draw() {
	for (int i=0;i<numOfJoints;i++) {
		(*joints)[i]->draw();
	}
}