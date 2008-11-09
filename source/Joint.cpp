#include "Joint.h"

/**
 * Constructor
 */
Joint::Joint(char *name, float x, float y, float z) {
	this->name = name;
	
	// Set coords
	this->x = x;
	this->y = y;
	this->z = z;
}

/*
 * Set parent
 */
void Joint::setParent(Joint *parent) {
	this->parent = parent;
}

/**
 * Add a new child.
 * Also increase children number.
 */
void Joint::addChild (Joint *child) {

	this->children->resize(this->childrenNumber+1);
	(*this->children)[this->childrenNumber++] = child;
}

/**
 * Get joint name
 */
char* Joint::getName () {
	return this->name;
}

/**
 * Get coords
 */
vector<float> Joint::getCoords() {
	vector<float> n;
	n.resize(3);
	n[0] = this->x;
	n[1] = this->y;
	n[2] = this->z;
	return n;
}

void Joint::draw() {
	

	
}