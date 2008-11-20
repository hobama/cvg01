#include "bvhframe.h"

/**
 * Constructor
 */
BVHFrame::BVHFrame() {

}

void BVHFrame::setPos(float x, float y, float z) {

	this->pos = new vector<float>(3);
	//this->pos->resize(3);
	(*this->pos)[0] = x;
	(*this->pos)[1] = y;
	(*this->pos)[2] = z;

}

void BVHFrame::setRot(float x, float y, float z) {

	this->rot = new vector<float>(3);
	//this->pos->resize(3);
	(*this->rot)[0] = x;
	(*this->rot)[1] = y;
	(*this->rot)[2] = z;

}