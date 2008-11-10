/*
 *  model.h
 *  objloader
 *
 *  Created by a1gucis on 10/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include "Polygon3.h"
#include "jointreader.h"
#include "objreader.h"
#include "Joint.h"
class Model{
private:
	Joint *rootJoint;
public:
	Model(char *jointFileName, char *meshDirectory); //for example /Users/a1gucis/Documents/meshes/
	void draw();
};

#endif
