/*
 *  vertex.h
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <math.h>
#include "vect.h"
#include "cvgMath.h"
class Vertex : public Vect {
private:
	bool connected;
	float drawX, drawY, drawZ;
public:
	Vertex(float x, float y, float z);
	void setConnected();
	bool isConnected();
	vector<float> *rotateVertex(float angle, vector<float> *vect); //returns vertex coordinates after rotation
	void setDrawX(float drawX);
	void setDrawY(float drawY);
	void setDrawZ(float drawZ);
	
	float getDrawX();
	float getDrawY();
	float getDrawZ();
};
#endif
