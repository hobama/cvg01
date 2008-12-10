/*
 *  cvgMath.cpp
 *  objloader
 *
 *  Created by a1gucis on 11/9/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "cvgMath.h"

using namespace std;
namespace cvgmath {
	float **matrixMult(float **matrix1, float **matrix2, int matrix1Rows, int matrix1Cols, int matrix2Rows, int matrix2Cols) {
		if (matrix1Cols != matrix2Rows) {
			cout<<"Matrix dimensions don't match"<<endl;
			return NULL;
		}
		float** resultMatrix = new float* [matrix1Rows];
		for (int i=0;i<matrix1Rows;i++) {
			float *resultMatrixRow = new float[matrix2Cols];
			(resultMatrix)[i] = resultMatrixRow;
		}
		//float **resultMatrix = new float[matrix1Rows][matrix2Cols];
		for (int z=0;z<matrix2Cols;z++) {
			for (int i=0;i<matrix1Rows;i++) {
				float sum = 0;
				for (int j=0;j<matrix1Cols;j++) {
					float element1 = matrix1[i][j];
					float element2 = matrix2[j][z];
					sum += element1 * element2;
				}
				resultMatrix[i][z] = sum;
			}
		}
		return resultMatrix;
	}
}