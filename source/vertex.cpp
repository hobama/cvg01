/*
 *  vertex.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "vertex.h"
#include "joint.h"
const float PI = 3.141592653;
Vertex::Vertex(float x, float y, float z) : Vect(x, y, z) {
	this->connected = false;
}

void Vertex::setConnected() {
	this->connected = true;
}

bool Vertex::isConnected(){
	return this->connected;
}
vector<float>* Vertex::rotateVertex(float angle, vector<float> *vect) {
	angle = PI/180.0 * angle;
	//	cout<<"Old: "<<(*position)[0]<<" "<<(*position)[1]<<" "<<(*position)[2]<<endl;
	float ux = (*vect)[0];
	float uy = (*vect)[1];
	float uz = (*vect)[2];
	//	cout<<"ux uy uz angle "<<ux<<" "<<uy<<" "<<uz<<" "<<angle<<endl;
	float s = sin(angle);
	float c = cos(angle);
	float **rotMatrix = new float* [4];
	
	float *row = new float[4];
	row[0] = c + (1-c)*ux*ux;
	row[1] = (1-c)*uy*ux-s*uz;
	row[2] = (1-c)*uz*ux+s*uy;
	row[3] = 0.0;
	rotMatrix[0] = row;
	
	row = new float[4];
	row[0] = (1-c)*ux*uy + s*uz;
	row[1] = c + (1-c)*uy*uy;
	row[2] = (1-c)*uz*uy - s*ux;
	row[3] = 0.0;
	rotMatrix[1] = row;
	
	row = new float[4];
	row[0] = (1-c)*ux*uz-s*uy;
	row[1] = (1-c)*uy*uz + s*ux;
	row[2] = c + (1-c)*uz*uz;
	row[3] = 0.0;
	rotMatrix[2] = row;
	
	row = new float[4];
	row[0] = 0.0;
	row[1] = 0.0;
	row[2] = 0.0;
	row[3] = 1.0;
	rotMatrix[3] = row;
	
	float **vertexCords = new float*[4];
	row = new float[1];
	row[0] = x;
	vertexCords[0] = row;
	
	row = new float[1];
	row[0] = y;
	vertexCords[1] = row;
	
	row = new float[1];
	row[0] = z;
	vertexCords[2] = row;
	
	row = new float[1];
	row[0] = 1.0;
	vertexCords[3] = row;
	
	float **newCords = cvgmath::matrixMult(rotMatrix, vertexCords, 4, 4, 4, 1);
	if (newCords != NULL) {
		vector<float> *newCordsVect = new vector<float>(3);
		(*newCordsVect)[0] = newCords[0][0];
		(*newCordsVect)[1] = newCords[1][0];
		(*newCordsVect)[2] = newCords[2][0];
		return newCordsVect;
	}else
		return NULL;
}
