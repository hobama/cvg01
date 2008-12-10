/*
 /*
 *  quaternion.h
 *  quaternion
 *
 *  Created by a1gucis on 12/9/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _QUATERNION_H_
#define _QUATERNION_H_
#include <math.h>
#include <iostream>
#include "cvgMath.h"
using namespace std;
class Quaternion {
private:
	float w, x, y, z;
	float angle;
public:
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	float getAngle();
	float getW();
	float getX();
	float getY();
	float getZ();
	float getVectorX();
	float getVectorY();
	float getVectorZ();
	void multiply(Quaternion *quaternion);
	void resetToInitial();
	void normalize();
};


#endif