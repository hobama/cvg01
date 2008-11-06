/*
 *  Polygon3.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Polygon3.h"

Polygon3::Polygon3(vector<Vertex *> *vertices, vector<Texel *> *texels, vector<Normal *> *normals) : Polygon(3) {
	this->vertices = vertices;
	this->texels = texels;
	this->normals = normals;
}