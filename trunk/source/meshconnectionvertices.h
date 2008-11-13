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
	
	bool rotated;
	vector<Vertex *> *mainVertices; 
	vector<Vertex *> *subVertices;
	int numOfSubVertices;
	
	void setSubVertices(); // count vertex positions in the line and fill up the vector
	float jointX, jointY, jointZ;
	
public:
	MeshConnectionVertices(float jointX, float jointY, float jointZ);
	
	void setVertices(vector<Vertex *> *mainVertices);
	vector<Vertex *> *getVertices();
	void draw();
	void updatePos(float angle, vector<float> *rotationVector);
};

#endif