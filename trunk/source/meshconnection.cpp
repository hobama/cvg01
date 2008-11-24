/*
 *  connection.cpp
 *  objloader
 *
 *  Created by a1gucis on 11/11/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "meshconnection.h"
const int INITIAL_VECTOR_SIZE = 64;
const float VECTOR_GROWTH = 0.5;
MeshConnection::MeshConnection(Mesh *mesh, Mesh *parentMesh, float distanceDev) {
	this->mesh = mesh;
	this->parentMesh = parentMesh;
	this->connectingVertices = new vector<MeshConnectionVertices *>(INITIAL_VECTOR_SIZE);
	this->numOfConnectingVertices = 0;
	this->distanceDev = distanceDev;
}

void MeshConnection::connectVertices(float jointX, float jointY, float jointZ) {
	this->jointX = jointX;
	this->jointY = jointY;
	this->jointZ = jointZ;
	vector<Vertex *> *verticesToConnect = new vector<Vertex *>(2);
	this->mainShortestDistance = shortestDistance(verticesToConnect);

	MeshConnectionVertices *meshConnectionVertices = new MeshConnectionVertices(jointX, jointY, jointZ);
	meshConnectionVertices->setVertices(verticesToConnect);
	(*connectingVertices)[numOfConnectingVertices++] = meshConnectionVertices;
	cout<<"shortestDistance: "<<mainShortestDistance<<endl;
	verticesToConnect = new vector<Vertex *>(2);
	while (mainShortestDistance + mainShortestDistance * distanceDev > shortestDistance(verticesToConnect)) {
		if (numOfConnectingVertices == connectingVertices->size()) {
			int newSize = floor(numOfConnectingVertices + numOfConnectingVertices * VECTOR_GROWTH);
			connectingVertices->resize(newSize);
		}
		MeshConnectionVertices *meshConnectionVertices = new MeshConnectionVertices(this->jointX, this->jointY, this->jointZ);
		meshConnectionVertices->setVertices(verticesToConnect);
		(*connectingVertices)[numOfConnectingVertices++] = meshConnectionVertices;
		verticesToConnect = new vector<Vertex *>(2);
	}
		
}

float MeshConnection::shortestDistance(vector<Vertex *> *verticesToConnect) {
	float shortestDistance = 0;
	vector<Vertex *> *parentVertices = parentMesh->getVertices();
	vector<Vertex *> *vertices = mesh->getVertices();
	
	Vertex *vertex = (*vertices)[0];
	Vertex *parentVertex = (*parentVertices)[0];
	shortestDistance = calcDistance(parentVertex, vertex);
	for (int i=0;i<parentMesh->getNumOfVertices();i++) {
		parentVertex = (*parentVertices)[i];
		if (!parentVertex->isConnected()) {
			for (int j=0;j<mesh->getNumOfVertices();j++) {
				vertex = (*vertices)[j];
				if (!vertex->isConnected()) {
					float dist = calcDistance(parentVertex, vertex);
					if (dist <= shortestDistance) {
						shortestDistance = dist;
						(*verticesToConnect)[0] = parentVertex;
						(*verticesToConnect)[1] = vertex;
					}
				}
			}
			
		}
	}
	vertex = (*verticesToConnect)[0];
	vertex->setConnected();
	vertex = (*verticesToConnect)[1];
	vertex->setConnected();
	return shortestDistance;
}

float MeshConnection::calcDistance(Vertex *vertex1, Vertex *vertex2) {
	float distance = 0.0;
	float x = (vertex1->getX() - vertex2->getX());
	float y = (vertex1->getY() - vertex2->getY());
	float z = (vertex1->getZ() - vertex2->getZ());
	
	distance = sqrt(x*x + y*y + z*z);
	
	return distance;
}

void MeshConnection::updatePos(float angle, vector<float> *rotationVector) {
	for (int i=0;i<numOfConnectingVertices;i++) {
		(*connectingVertices)[i]->updatePos(angle, rotationVector);
	}
}

void MeshConnection::draw() {
	glPushMatrix();
	for (int i=0;i<numOfConnectingVertices;i++) {
		(*connectingVertices)[i]->draw();
	}
	const float color[]= {1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
		
	for (int i=0;i<numOfConnectingVertices - 1;i++) {
		vector<Vertex *> *vertices1 = (*connectingVertices)[i]->getVertices();
		vector<Vertex *> *vertices2 = (*connectingVertices)[i+1]->getVertices();
		drawPolygons(vertices1, vertices2);
	}
	glPopMatrix();
}

void MeshConnection::drawPolygons(vector<Vertex *> *vertices1, vector<Vertex *> *vertices2) {
	if (vertices1->size() != vertices2->size()) 
		cout<<"ERROR in MeshConnection class: vertices vector size don't match"<<endl;
	else {
		for (int i=0;i<vertices1->size()-1;i++) {
			Vertex *vertex1 = (*vertices1)[i];
			Vertex *vertex2 = (*vertices1)[i+1];
			Vertex *vertex3 = (*vertices2)[i+1];
			Vertex *vertex4 = (*vertices2)[i];
			
			glBegin(GL_QUADS);
			glVertex3f(vertex1->getX(), vertex1->getY(), vertex1->getZ());
			glVertex3f(vertex2->getX(), vertex2->getY(), vertex2->getZ());
			glVertex3f(vertex3->getX(), vertex3->getY(), vertex3->getZ());
			glVertex3f(vertex4->getX(), vertex4->getY(), vertex4->getZ());
			glEnd();
		}
	}
}