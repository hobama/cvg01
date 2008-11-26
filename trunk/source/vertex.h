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
	float originalX, originalY, originalZ;
	bool connected;
public:
	Vertex(float x, float y, float z);
	float getOriginalX();
	float getOriginalY();
	float getOriginalZ();
	void setRotation(float **rotationMatrix, float x, float y, float z);
	void setTranslation(float x, float y, float z);
	void setConnected();
	bool isConnected();
	
	void rotateVertex(float angle, vector<float> *vect, float x, float y, float z); //returns vertex coordinates after rotation

};
#endif
