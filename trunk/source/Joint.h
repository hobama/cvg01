#ifndef _JOINT_H_
#define _JOINT_H_
#include <string>
#include <vector>
#include "mesh.h"
#include "Polygon3.h"
#include "vertex.h"
#include "meshconnection.h"
class Joint {
private:
	char *name;
	float x,y,z;
	Joint *parent;
	int childrenNumber;
	vector<Joint *> *children;
	Mesh *mesh;
	MeshConnection *meshConnection;
	float rotationAngle;
	vector<float> *rotationVector;
public:
	Joint(char *name, float x, float y, float z);
	void setParent(Joint *parent);
	void addChild (Joint *child);
	
	char *getName();
	vector<float> getCoords();
	void setMesh(Mesh *mesh);
	Mesh *getMesh();
	
	void setRotation(float rotationAngle, vector<float> *rotationVector);
	void createMeshConnection();
	void draw(bool drawMesh);
	void debugJoint();
};
#endif