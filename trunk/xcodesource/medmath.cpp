/*
 *  medMath.cpp
 *  particles
 *
 *  Created by a1gucis on 9/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "medmath.h"
#include <iostream>

using namespace std;
namespace medMath {
	vector<float> matrixMult(vector<float> &matrix, vector<float> &vDir){
		vector<float> newDir(vDir);
		if (newDir.size()<3)
			cout<<"error in matrixMult: point size smaller 3"<<endl;
		if (newDir.size()==3)
			newDir.push_back(1);
		
		if (matrix.size()!=16) 
			cout<<"error in matrixMult: matrix size not 16"<<endl;
		else {
			newDir[0] = matrix[0]*vDir[0] +  matrix[4]*vDir[1] + matrix[8]*vDir[2] + matrix[12]*vDir[3];
			newDir[1] = matrix[1]*vDir[0] +  matrix[5]*vDir[1] + matrix[9]*vDir[2] + matrix[13]*vDir[3];
			newDir[2] = matrix[2]*vDir[0] +  matrix[6]*vDir[1] + matrix[10]*vDir[2] + matrix[14]*vDir[3];
			newDir[3] = matrix[3]*vDir[0] +  matrix[7]*vDir[1] + matrix[11]*vDir[2] + matrix[15]*vDir[3];
		}
		if (vDir.size()==3) {
			newDir[0]/=newDir[3];
			newDir[1]/=newDir[3];
			newDir[2]/=newDir[3];
			newDir.pop_back();
		}
		return newDir;
	}
	
	
	std::vector<float> crossProduct(const std::vector<float> &v, 
									const std::vector<float> &w)
	{
		std::vector<float> destvec(3);
		destvec[0] = v[1] * w[2] - v[2] * w[1];
		destvec[1] = v[2] * w[0] - v[0] * w[2];
		destvec[2] = v[0] * w[1] - v[1] * w[0];
		
		return destvec;
	}
	
	// added const as in the decleration
	double length(const std::vector<float> &v)
	{
		float length=0;
		for (unsigned int i=0; i<v.size(); i++) 
			length+= v[i]*v[i];
		return sqrt(length);
	}
	
	void normalize(std::vector<float> &v)
	{
		float length=0;
		for (unsigned int i=0; i<v.size(); i++) 
			length+= v[i]*v[i];
		length=sqrt(length);
		for (unsigned int j=0; j<v.size(); j++) 
			v[j]/=length; 
	}
	
	
	void scale(std::vector<float> &a, float scale)
	{
		for (unsigned int i=0; i<a.size(); i++) 
			a[i]*= scale;
	}
	
	std::vector<float> minus(const std::vector<float> &a, const std::vector<float> &b)
	{
		std::vector<float> res(3);
		res[0]=a[0]-b[0];
		res[1]=a[1]-b[1];
		res[2]=a[2]-b[2];
		return res;
	}
	
	std::vector<float> add(const std::vector<float> &a, const std::vector<float> &b)
	{
		std::vector<float> res(3);
		res[0]=a[0]+b[0];
		res[1]=a[1]+b[1];
		res[2]=a[2]+b[2];
		return res;
	}
	
} // namespace



