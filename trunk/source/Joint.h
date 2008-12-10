#ifndef _JOINT_H_
#define _JOINT_H_
#include <string>
#include <vector>
#include "mesh.h"
#include "Polygon3.h"
#include "vertex.h"
#include "meshconnection.h"
#include "bvhframe.h"
#include "frame.h"
#include "quaternion.h"
class Joint {
private:
	char *name;
	float x,y,z;
	Joint *parent;
	int childrenNumber;
	vector<Joint *> *children;
	Mesh *mesh;
	MeshConnection *meshConnection;
	float directionX, directionY, directionZ;
	float angle;
	vector<BVHFrame *> *bvhframes;
	vector<Frame *> *frames;
	vector<char> *rotationSequence;
	Quaternion *total;
public:
	Joint(char *name, float x, float y, float z);
	void setParent(Joint *parent);
	Joint *getParent();
	void addChild (Joint *child);
	char *getName();
	vector<float> getCoords();
	void setMesh(Mesh *mesh);
	Mesh *getMesh();
	void setFrames(vector<BVHFrame *> *frames);
	vector<Frame *>* getFrames();
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setRotationSequence(vector<char> *rotationSequence);
	void setTranslation(float x, float y, float z);
	void addTranslation(float x, float y, float z);
	void createMeshConnection();
	void updateFrame(int frameNumber);
	void draw(bool drawMesh);
	void debugJoint();
};
#endif