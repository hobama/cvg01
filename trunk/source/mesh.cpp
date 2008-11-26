/*
 *  mesh.cpp
 *  objloader
 *
 *  Created by a1gucis on 11/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "mesh.h"

Mesh::Mesh(vector<Polygon3 *> *polygons, int numOfPolygons) {
	this->polygons = polygons;
	this->numOfPolygons = numOfPolygons;
	this->offsetX = 0.0;
	this->offsetY = 0.0;
	this->offsetZ = 0.0;
}

void Mesh::setTranslation(float x, float y, float z) {
	this->offsetX = x;
	this->offsetY = y;
	this->offsetZ = z;
	Vertex *vertex;
	for (int i=0;i<numOfVertices;i++){
		vertex = (*vertices)[i];
		vertex->setTranslation(x, y, z);		
	}
	
}

void Mesh::setRotation(float **rotationMatrix, float jointX, float jointY, float jointZ) {
	for (int i=0;i<numOfVertices;i++){
		Vertex *vertex = (*vertices)[i];
		vertex->setRotation(rotationMatrix, jointX, jointY, jointZ);
	}
	
}
void Mesh::draw() {
	Polygon3 *polygon;
	for (int i=0;i<numOfPolygons;i++){
		polygon = (*polygons)[i];
		polygon->draw();

	}
}
void Mesh::setVertices(vector<Vertex *> *vertices, int numOfVertices) {
	this->vertices = vertices;
	this->numOfVertices = numOfVertices;
}

vector<Vertex *>* Mesh::getVertices() {
	return this->vertices;
}

int Mesh::getNumOfVertices() {
	return this->numOfVertices;
}
