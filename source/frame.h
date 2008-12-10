/*
 *  frame.h
 *  objloader
 *
 *  Created by a1gucis on 12/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _FRAME_H_
#define _FRAME_H_
#include "bvhframe.h"
class Frame {
private:
	float angle;
	float directionX, directionY, directionZ;
	vector<float> *pos;
public:
	Frame(float angle, float x, float y, float z);
	float getAngle();
	float getDirectionX();
	float getDirectionY();
	float getDirectionZ();
	
	void setPos(vector<float> *pos);
	vector<float> *getPos();
};

#endif
