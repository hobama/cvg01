/*
 *  Polygon3.h
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _POLYGON3_H_
#define _POLYGON3_H_
#include "polygon.h"
class Polygon3 : public Polygon {
public:
	Polygon3(vector<Vertex *> *vertices, vector<Texel *> *texels, vector<Normal *> *normals);
};
#endif