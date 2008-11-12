/*
 *  vertex.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "vertex.h"

Vertex::Vertex(float x, float y, float z) : Vect(x, y, z) {
	this->connected = false;
}

void Vertex::setConnected() {
	this->connected = true;
}

bool Vertex::isConnected(){
	return this->connected;
}