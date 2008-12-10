#ifndef _MESH_CONNECTION_VERTICES_H_
#define _MESH_CONNECTION_VERTICES_H_
#include <vector>
#include <iostream>
#include <math.h>
#include "vertex.h"
#include "systeminclude.h"

using namespace std;

class MeshConnectionVertices {
private:
	vector<Vertex *> *mainVertices; 
	vector<Vertex *> *subVertices;
	int numOfSubVertices;
	void setSubVertices(); // count vertex positions in the line and fill up the vector
	float jointX, jointY, jointZ;
	float x, y, z;
public:
	MeshConnectionVertices(float jointX, float jointY, float jointZ);
	
	void setVertices(vector<Vertex *> *mainVertices);
	vector<Vertex *> *getVertices();
	void draw();
	void addTranslation(float x, float y, float z);
	void updatePos(float angle, vector<float> *rotationVector);
	void resetRotation();
};

#endif