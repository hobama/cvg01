/*
 *  vertex.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "vertex.h"
const float PI = 3.141592653;
Vertex::Vertex(float x, float y, float z) : Vect(0.0, 0.0, 0.0) {
	this->connected = false;
	this->originalX = x;
	this->originalY = y;
	this->originalZ = z;
}
float Vertex::getOriginalX() {
	return this->originalX;
}
float Vertex::getOriginalY() {
	return this->originalY;
}
float  Vertex::getOriginalZ() {
	return this->originalZ;
}

void Vertex::setRotation(float **rotationMatrix, float x, float y, float z) {
	this->originalX = this->originalX - x;
	this->originalY = this->originalY - y;
	this->originalZ = this->originalZ - z;
	//rotation
	
	float *row;
	float **vertexCords = new float*[4];
	row = new float[1];
	row[0] = originalX;
	vertexCords[0] = row;
	
	row = new float[1];
	row[0] = originalY;
	vertexCords[1] = row;
	
	row = new float[1];
	row[0] = originalZ;
	vertexCords[2] = row;
	
	row = new float[1];
	row[0] = 1.0;
	vertexCords[3] = row;
	
	float **newCords = cvgmath::matrixMult(rotationMatrix, vertexCords, 4, 4, 4, 1);
	if (newCords != NULL) {
		this->originalX = newCords[0][0];
		this->originalY = newCords[1][0];
		this->originalZ = newCords[2][0];
		delete[] newCords;
	}
	delete[] vertexCords;
	
	//rotation end
	this->originalX = this->originalX + x;
	this->originalY = this->originalY + y;
	this->originalZ = this->originalZ + z;
}
void Vertex::setTranslation(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
void Vertex::setConnected() {
	this->connected = true;
}

bool Vertex::isConnected(){
	return this->connected;
}

void Vertex::rotateVertex(float angle, vector<float> *vect, float x, float y, float z) {
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
	row[0] = originalX - x;
	vertexCords[0] = row;
	
	row = new float[1];
	row[0] = originalY - y;
	vertexCords[1] = row;
	
	row = new float[1];
	row[0] = originalZ - z;
	vertexCords[2] = row;
	
	row = new float[1];
	row[0] = 1.0;
	vertexCords[3] = row;
	
	float **newCords = cvgmath::matrixMult(rotMatrix, vertexCords, 4, 4, 4, 1);
	if (newCords != NULL) {
		this->originalX = newCords[0][0] + x;
		this->originalY = newCords[1][0] + y;
		this->originalZ = newCords[2][0] + z;
	}
}

