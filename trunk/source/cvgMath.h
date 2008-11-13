/*
 *  cvgMath.h
 *  objloader
 *
 *  Created by a1gucis on 11/9/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CVG_MATH_H
#define CVG_MATH_H
#include <iostream>
#include <vector>
namespace cvgmath {
	using namespace std;
	float **matrixMult(float **matrix1, float **matrix2, int matrix1Rows, int matrix1Cols, int matrix2Rows, int matrix2Cols);
}

#endif