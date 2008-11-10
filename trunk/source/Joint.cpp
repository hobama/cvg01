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

	// Parent
	this->parent = NULL;

	// Children
	this->children = new vector<Joint *>;
	this->childrenNumber = 0;
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
	//cout << this->childrenNumber << endl;
	(*this->children)[this->childrenNumber++] = child;
}

/**
 * Get joint name
 */
char *Joint::getName () {
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
	glPushMatrix();

	glTranslatef(x, y, z);
	const float color[]= {0.1, 0.5, 1.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glutSolidSphere(0.1,10,10);

	glPopMatrix();
}

/**
 * Debug
 */
void Joint::debugJoint() {
	cout << "-----------------" << endl;

	cout << "Name" << this->name << endl;

	if(this->parent != NULL)
		cout << " Parent " << this->parent->getName() << endl;


	for (int i=0;i<childrenNumber;i++) {
		cout << "  Child " << (*this->children)[i]->getName() << endl;
	}
	cout << "-----------------" << endl;
}