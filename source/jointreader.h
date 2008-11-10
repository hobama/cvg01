
#ifndef _JOINTREADER_H_
#define _JOINTREADER_H_
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Joint.h"
#include "Polygon3.h"
using namespace std;

const int JOINT_NAME_SIZE = 20;

class JointReader {
private: 
	char *filename;
	vector<Joint *> *joints;
	int numOfJoints;
	Joint *rootJoint;
	void readJointData(ifstream *datafile);
public:
	JointReader(char *filename);
	void readData();

	Joint *findJointByName(char *name);
	vector<Joint *> *getJoints();
	int getNumOfJoints();
	Joint *getRootJoint();
	//
};


#endif