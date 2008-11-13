/*
 *  point.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "vect.h"

Vect::Vect(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vect::getX() {
	return x;
}

float Vect::getY() {
	return y;
}

float Vect::getZ() {
	return z;
}

void Vect::setX(float x) {
	this->x = x;
}	

void Vect::setY(float y) {
	this->y = y;
}

void Vect::setZ(float z) {
	this->z = z;
}
