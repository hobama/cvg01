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
	
	// Mesh
	this->mesh = NULL;
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

void Joint::setMesh(Mesh *mesh) {
	this->mesh = mesh;
}

Mesh* Joint::getMesh() {
	return this->mesh;
}
void Joint::draw(bool drawMesh) {
	glPushMatrix();
	
	glTranslatef(x, y, z);
	const float color[]= {0.1, 0.5, 1.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glutSolidSphere(0.1,10,10);
	if (strcmp(this->name,"left_knee") == 0)
		glRotatef(90, 1, 0, 0);
	glTranslatef(-1 * x, -1 * y, -1 * z);
	if ((drawMesh) && (this->mesh != NULL))
		this->mesh->draw();
	for (int i=0;i<childrenNumber;i++) {
		Joint *child = (*children)[i];
		vector<float> coords = child->getCoords();
		glMaterialfv(GL_FRONT, GL_AMBIENT, color);
		glBegin(GL_LINES);
		glVertex3f(x, y, z);
		glVertex3f((coords)[0], (coords)[1], (coords)[2]);
		glEnd();
		child->draw(drawMesh);
	}
	
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