/*
 *  medMath.h
 *  particles
 *
 *  Created by a1gucis on 9/22/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __medMath_H_
#define __medMath_H_
#include <vector>

#define _USE_MATH_DEFINES 
#include "math.h"


// simple math functions as developed for Medialogi OpenGL programming and AI
// all functions work on 3D vectors/points
namespace medMath
{
	using namespace std;
	vector<float> matrixMult(vector<float> &matrix, vector<float> &vDir);
	
	std::vector<float> crossProduct(const std::vector<float> &v, 
									const std::vector<float> &w);
	
	void normalize(std::vector<float> &v);
	
	double length(const std::vector<float> &v);
	
	
	
	std::vector<float> minus(const std::vector<float> &a, const std::vector<float> &b);
	inline std::vector<float> operator-(const std::vector<float> &a, const std::vector<float> &b) 
	{ return medMath::minus(a,b); }
	
	std::vector<float> add(const std::vector<float> &a, const std::vector<float> &b);
	inline std::vector<float> operator+(const std::vector<float> &a, const std::vector<float> &b) 
	{ return add(a,b); }
	
	void scale(std::vector<float> &a, float scale);
	
	inline std::vector<float> operator*(const std::vector<float> &v, double s) 
	{ std::vector<float> res(v);
		scale(res,float(s)); 
		return res;
	}
	
	inline std::vector<float> operator*(double s, const std::vector<float> &v) 
	{ return v*s; }
	
	inline std::vector<float> operator*(float s, const std::vector<float> &v) 
	{ return v*s; }
	
	
	inline std::vector<float> operator*(const std::vector<float> &v, float s) 
	{ std::vector<float> res(v);
		scale(res,float(s)); 
		return res; 
	}
	
};
#endif


