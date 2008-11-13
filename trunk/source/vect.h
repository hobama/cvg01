/*
 *  point.h
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _VECT_H_
#define _VECT_H_

#include <vector>
using namespace std;
class Vect {
protected:
	float x, y, z;
	
public:
	Vect(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
};
#endif