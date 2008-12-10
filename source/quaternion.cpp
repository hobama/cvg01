/*
 *  quaternion.cpp
 *  quaternion
 *
 *  Created by a1gucis on 12/9/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "quaternion.h"
const float PI = 3.141592653;
const float THRESHOLD = 0.000000005;
Quaternion::Quaternion() {
	this->angle = 0.0;
	this->w = 1.0;
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}
Quaternion::Quaternion(float angle, float x, float y, float z) {
	this->angle = angle;
	angle = angle/180 * PI;
	angle /= 2.0;
	this->w = cos(angle);
	this->x = x * sin(angle);
	this->y = y * sin(angle);
	this->z = z * sin(angle);
}

void Quaternion::resetToInitial() {
	this->angle = 0.0;
	this->w = 1.0;
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;	
}
float Quaternion::getAngle() {
	return 180 * (acos(w) * 2) / PI;
}
float Quaternion::getVectorX() {
	float sin_w = sqrt(1 - w * w);
	if ( fabs( sin_w ) < 0.0005 )
		sin_w = 1;
	
	return this->x/sin_w;
}

float Quaternion::getVectorY() {
	float sin_w = sqrt(1 - w * w);
	if ( fabs( sin_w ) < 0.0005 )
		sin_w = 1;
	
	return this->y/sin_w;
}

float Quaternion::getVectorZ() {
	float sin_w = sqrt(1 - w * w);
	if ( fabs( sin_w ) < 0.0005 )
		sin_w = 1;
	
	return this->z/sin_w;
}
float Quaternion::getW() {
	return this->w;
}
float Quaternion::getX() {
	return this->x;
}
float Quaternion::getY() {
	return this->y;
}
float Quaternion::getZ() {
	return this->z;
}
void Quaternion::normalize() {
	float magnitude = w*w + x*x + y*y + z*z;
	if (fabs(1 - magnitude) > THRESHOLD) {
		magnitude = sqrt(w*w + x*x + y*y + z*z);
		w /= magnitude;
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}
void Quaternion::multiply(Quaternion *quaternion) {
	float w2 = quaternion->getW();
	float x2 = quaternion->getX();
	float y2 = quaternion->getY();
	float z2 = quaternion->getZ();
	
	float new_w = w2*w - x2*x - y2*y - z2*z;
	float new_x = w2*x + x2*w + y2*z - z2*y;
	float new_y = w2*y - x2*z + y2*w + z2*x;
	float new_z = w2*z + x2*y - y2*x + z2*w;
	
	w = new_w;
	x = new_x;
	y = new_y;
	z = new_z;
}