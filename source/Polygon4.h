/*
 *  Polygon4.h
 *  objloader
 *
 *  Created by a1gucis on 11/7/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef POLYGON_4_H
#define POLYGON_4_H
#include "polygon.h"

class Polygon4 : public Polygon {
public:
	Polygon4(vector<Vertex *> *vertices, vector<Texel *> *texels, vector<Normal *> *normals);
};

#endif