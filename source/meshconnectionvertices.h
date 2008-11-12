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

public:
	MeshConnectionVertices();

	void setVertices(vector<Vertex *> *mainVertices);

	void draw();
};

#endif