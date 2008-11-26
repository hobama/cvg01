/*
 *  connection.h
 *  objloader
 *
 *  Created by a1gucis on 11/11/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MESH_CONNECTION_H_
#define _MESH_CONNECTION_H_
#include <vector>
#include <iostream>
#include <math.h>
#include "systeminclude.h"
#include "mesh.h"
#include "meshconnectionvertices.h"
#include "vertex.h"


class MeshConnection {
private:
	Mesh *mesh, *parentMesh;
	vector<MeshConnectionVertices *> *connectingVertices; 
	int numOfConnectingVertices;
	float *jointX, *jointY, *jointZ;
	float offsetX, offsetY, offsetZ;
	float distanceDev;
	float mainShortestDistance;
	float shortestDistance(vector<Vertex *> *verticesToConnect); // finds the distance between the closest vertices 
	float calcDistance(Vertex *vertex1, Vertex *vertex2);
	void drawPolygons(vector<Vertex *> *vertices1, vector<Vertex *> *vertices2);
public:
	MeshConnection(Mesh *mesh, Mesh *parentMesh, float distanceDev);
	void connectVertices(float *jointX, float *jointY, float *jointZ);
	void rotate(float angle, vector<float> *rotationVector);
	void setTranslation(float x, float y, float z);
	void setRotation(float **rotationMatrix, float jointX, float jointY, float jointZ);
	void draw();
};

#endif