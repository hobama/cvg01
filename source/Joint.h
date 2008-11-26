#ifndef _JOINT_H_
#define _JOINT_H_
#include <string>
#include <vector>
#include "mesh.h"
#include "Polygon3.h"
#include "vertex.h"
#include "meshconnection.h"
#include "cvgMath.h"
#include "bvhframe.h"
class Joint {
private:
	char *name;
	float offsetX, offsetY, offsetZ;
	float originalX, originalY, originalZ;
	Joint *parent;
	int childrenNumber;
	vector<Joint *> *children;
	Mesh *mesh;
	MeshConnection *meshConnection;
	vector<BVHFrame *> *frames;
	
	vector<float> *rotationVector;
	void updateTranslation(float x, float y, float z);
	void rotate(float **rotationMatrix, float originalX, float originalY, float originalZ);
	void rotateMeshConnection(float **rotationMatrix, float jointX, float jointY, float jointZ);
public:
	Joint(char *name, float x, float y, float z);
	void setParent(Joint *parent);
	void addChild (Joint *child);
	
	Joint *getParent();
	char *getName();
	vector<float> getCoords();
	void setMesh(Mesh *mesh);
	Mesh *getMesh();
	MeshConnection *getMeshConnection();
	
	void setFrames(vector<BVHFrame *> *frames);
	vector<BVHFrame *>* getFrames();
	float getOriginalX();
	float getOriginalY();
	float getOriginalZ();
	void setOriginalXYZ(float x, float y, float z);
	void setRotation(float rotationAngle, vector<float> *rotationVector);
	void setTranslation(float x, float y, float z);
	void createMeshConnection();
	void updateFrame(int frameNumber);
	void draw(bool drawMesh);
	void debugJoint();
};
#endif