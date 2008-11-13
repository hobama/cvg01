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
	
	//Mesh connection
	this->meshConnection = NULL;
	// Children
	this->children = new vector<Joint *>;
	this->childrenNumber = 0;
	
	this->rotationAngle = 0.0;
	this->rotationVector = NULL;
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

void Joint::createMeshConnection() {
	if ((this->mesh != NULL) && (parent->getMesh() != NULL)) {
		this->meshConnection = new MeshConnection(this->mesh, parent->getMesh(), 0.2);
		cout<<name<<" in connectVertices()"<<endl;
		this->meshConnection->connectVertices(this->x, this->y, this->z);
	}

}
Mesh* Joint::getMesh() {
	return this->mesh;
}

void Joint::setRotation(float rotationAngle, vector<float> *rotationVector) {
	

	// update pos
	if (meshConnection != NULL)
		meshConnection->updatePos(rotationAngle - this->rotationAngle, rotationVector);
	
	this->rotationAngle = rotationAngle;
	this->rotationVector = rotationVector;
}
float Joint::getRotationAngle() {
	return this->rotationAngle;
}
void Joint::draw(bool drawMesh) {
	glPushMatrix();
	
	if (meshConnection != NULL)
		meshConnection->draw();
	glTranslatef(x, y, z);
	const float color[]= {0.1, 0.5, 1.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glutSolidSphere(0.1,10,10);
	
	if ((rotationAngle != 0) && (rotationVector != NULL))
		glRotatef(rotationAngle, (*rotationVector)[0], (*rotationVector)[1], (*rotationVector)[2]);
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