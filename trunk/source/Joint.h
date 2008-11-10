#ifndef _JOINT_H_
#define _JOINT_H_
#include "Polygon3.h"
class Joint {
private:
	char *name;
	float x,y,z;
	Joint *parent;
	int childrenNumber;
	vector<Joint *> *children;
	vector<Polygon3 *> *polygons;

public:
	Joint(char *name, float x, float y, float z);
	void setParent(Joint *parent);
	void addChild (Joint *child);
	
	char *getName();
	vector<float> getCoords();
	
	void draw();
	void debugJoint();
};
#endif