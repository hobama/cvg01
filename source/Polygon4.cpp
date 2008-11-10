/*
 *  Polygon4.cpp
 *  objloader
 *
 *  Created by a1gucis on 11/7/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Polygon4.h"

Polygon4::Polygon4(vector<Vertex *> *vertices, vector<Texel *> *texels, vector<Normal *> *normals) : Polygon(4) {
	this->vertices = vertices;
	this->texels = texels;
	this->normals = normals;
}