#ifndef _JOINTBUILDER_H_
#define _JOINTBUILDER_H_
#include <vector>
#include "Joint.h"
using namespace std;

class JointBuilder {
private: 
	int numOfJoints;
	Joint *rootJoint;
	vector<Joint *> *joints;
public:
	JointBuilder(vector<Joint *> *joints, int numOfJoints, Joint *rootJoint);
	void draw();
	//
};


#endif