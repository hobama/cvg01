
#ifndef _JOINTBUILDER_H_
#define _JOINTBUILDER_H_
#include <vector>
#include "Joint.h"
using namespace std;

class JointBuilder {
private: 
	int numOfJoints;
	vector<Joint *> *joints;
public:
	JointBuilder(vector<Joint *> *joints, int numOfJoints);
	void draw();
	//
};


#endif