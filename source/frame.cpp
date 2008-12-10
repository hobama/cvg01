/*
 *  frame.cpp
 *  objloader
 *
 *  Created by a1gucis on 12/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "frame.h"

Frame::Frame(float angle, float x, float y, float z) {
	this->angle = angle;
	this->directionX = x;
	this->directionY = y;
	this->directionZ = z;
	this->pos = NULL;
}

float Frame::getAngle() {
	return this->angle;
}

float Frame::getDirectionX() {
	return this->directionX;
}

float Frame::getDirectionY() {
	return this->directionY;
}

float Frame::getDirectionZ() {
	return this->directionZ;
}

void Frame::setPos(vector<float> *pos) {
	this->pos = pos;
}

vector<float> *Frame::getPos() {
	return this->pos;
}