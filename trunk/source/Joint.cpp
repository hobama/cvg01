#include "Joint.h"

/**
 * Constructor
 */
const float PI = 3.141592653;

Joint::Joint(char *name, float x, float y, float z) {
	this->name = name;
	
	// Set coords
	this->originalX = x;
	this->originalY = y;
	this->originalZ = z;
	
	this->offsetX = 0.0;
	this->offsetY = 0.0;
	this->offsetZ = 0.0;
	// Parent
	this->parent = NULL;
	
	// Mesh
	this->mesh = NULL;
	
	//Mesh connection
	this->meshConnection = NULL;
	
	//Frames
	this->frames = NULL;
	
	// Children
	this->children = new vector<Joint *>;
	this->childrenNumber = 0;
	this->rotationVector = NULL;
	
}

Joint* Joint::getParent() {
	return this->parent;
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
	n[0] = this->originalX + offsetX;
	n[1] = this->originalY + offsetY;
	n[2] = this->originalZ + offsetZ;
	return n;
}

void Joint::setMesh(Mesh *mesh) {
	this->mesh = mesh;
}

void Joint::createMeshConnection() {
	if ((this->mesh != NULL) && (parent->getMesh() != NULL)) {
		this->meshConnection = new MeshConnection(this->mesh, parent->getMesh(), 0.4);
		cout<<name<<" in connectVertices()"<<endl;
		this->meshConnection->connectVertices(&(this->originalX), &(this->originalY), &(this->originalZ));
	}

}
Mesh* Joint::getMesh() {
	return this->mesh;
}

MeshConnection* Joint::getMeshConnection() {
	return this->meshConnection;
}

void Joint::setFrames(vector<BVHFrame *> *frames) {
	this->frames = frames;
}

vector<BVHFrame *>* Joint::getFrames() {
	return this->frames;
}
void Joint::rotate(float **rotationMatrix, float originalX, float originalY, float originalZ) {
	float *row;
	float **jointCords = new float*[4];
	row = new float[1];
	row[0] = this->originalX;
	jointCords[0] = row;
	
	row = new float[1];
	row[0] = this->originalY;
	jointCords[1] = row;
	
	row = new float[1];
	row[0] = this->originalZ;
	jointCords[2] = row;
	
	row = new float[1];
	row[0] = 1.0;
	jointCords[3] = row;
	
	float **newCords = cvgmath::matrixMult(rotationMatrix, jointCords, 4, 4, 4, 1);
	if (newCords != NULL) {
		this->originalX = newCords[0][0];
		this->originalY = newCords[1][0];
		this->originalZ = newCords[2][0];
		delete[] newCords;
	}
	delete[] jointCords;
	if (this->mesh != NULL)
		mesh->setRotation(rotationMatrix, originalX, originalY, originalZ);
	for (int i=0;i<childrenNumber;i++) {
		Joint *child = (*children)[i];
		child->rotate(rotationMatrix, originalX, originalY, originalZ);
	}
}
void Joint::rotateMeshConnection(float **rotationMatrix, float jointX, float jointY, float jointZ) {
	for (int i=0;i<childrenNumber;i++) {
		Joint *joint = (*children)[i];
		MeshConnection *mConnection = joint->getMeshConnection();
		if (mConnection != NULL) 
			mConnection->setRotation(rotationMatrix, jointX, jointY, jointZ);
		joint->rotateMeshConnection(rotationMatrix, jointX, jointY, jointZ);
	}
}

float Joint::getOriginalX() {
	return this->originalX;
}

float Joint::getOriginalY() {
	return this->originalY;
}

float Joint::getOriginalZ() {
	return this->originalZ;
}
void Joint::setOriginalXYZ(float x, float y, float z) {
	this->originalX = x;
	this->originalY = y;
	this->originalZ = z;
}
void Joint::setRotation(float angle, vector<float> *rotationVector) {
	

	// update pos
	if (meshConnection != NULL)
		meshConnection->rotate(angle, rotationVector);
	
	this->rotationVector = rotationVector;
	
	//###############
	angle = PI/180.0 * angle;
	//	cout<<"Old: "<<(*position)[0]<<" "<<(*position)[1]<<" "<<(*position)[2]<<endl;
	float ux = (*rotationVector)[0];
	float uy = (*rotationVector)[1];
	float uz = (*rotationVector)[2];
	//	cout<<"ux uy uz angle "<<ux<<" "<<uy<<" "<<uz<<" "<<angle<<endl;
	float s = sin(angle);
	float c = cos(angle);
	float **rotMatrix = new float* [4];
	
	float *row = new float[4];
	row[0] = c + (1-c)*ux*ux;
	row[1] = (1-c)*uy*ux-s*uz;
	row[2] = (1-c)*uz*ux+s*uy;
	row[3] = 0.0;
	rotMatrix[0] = row;
	
	row = new float[4];
	row[0] = (1-c)*ux*uy + s*uz;
	row[1] = c + (1-c)*uy*uy;
	row[2] = (1-c)*uz*uy - s*ux;
	row[3] = 0.0;
	rotMatrix[1] = row;
	
	row = new float[4];
	row[0] = (1-c)*ux*uz-s*uy;
	row[1] = (1-c)*uy*uz + s*ux;
	row[2] = c + (1-c)*uz*uz;
	row[3] = 0.0;
	rotMatrix[2] = row;
	
	row = new float[4];
	row[0] = 0.0;
	row[1] = 0.0;
	row[2] = 0.0;
	row[3] = 1.0;
	rotMatrix[3] = row;
	float tX = this->originalX;
	float tY = this->originalY;
	float tZ = this->originalZ;
	updateTranslation(-1 * tX, -1 * tY, -1 * tZ);
	rotate(rotMatrix, tX, tY, tZ);
	updateTranslation(tX, tY, tZ);
	
	if (this->meshConnection != NULL)
		meshConnection->rotate(angle, rotationVector);
	rotateMeshConnection(rotMatrix, tX, tY, tZ);
	//##############
	
}
void Joint::setTranslation(float x, float y, float z) {
	this->offsetX = x;
	this->offsetY = y;
	this->offsetZ = z;
	if (this->mesh != NULL)
		mesh->setTranslation(x, y, z);
	if (this->meshConnection != NULL)
		meshConnection->setTranslation(x, y, z);
	for (int i=0;i<childrenNumber;i++) {
		Joint *joint = (*children)[i];
		joint->setTranslation(x, y, z);
	}
	
}
void Joint::updateTranslation(float x, float y, float z) {
	this->originalX = this->originalX + x;
	this->originalY = this->originalY + y;
	this->originalZ = this->originalZ + z;
	for (int i=0;i<childrenNumber;i++) {
		Joint *joint = (*children)[i];
		joint->updateTranslation(x, y, z);
	}
}
void Joint::updateFrame(int frameNumber) {
	if (frames != NULL) {
		BVHFrame *frame = (*frames)[frameNumber];
		vector<float> *pos = frame->getPos();
		vector<float> *rotation = frame->getRot();
		if (pos != NULL) {
			
			//this->setTranslation((*pos)[0] - this->originalX, (*pos)[1] - this->originalY, (*pos)[2] - this->originalZ);
		}
		if (rotation != NULL) {
			vector <float> *rotationVector = new vector<float>(3);
			//rotate by x axis
			(*rotationVector)[0] = 1.0;
			(*rotationVector)[1] = 0.0;
			(*rotationVector)[2] = 0.0;
			this->setRotation((*rotation)[0], rotationVector);
			
			//rotate by y axis
			(*rotationVector)[0] = 0.0;
			(*rotationVector)[1] = 1.0;
			(*rotationVector)[2] = 0.0;
			this->setRotation((*rotation)[1], rotationVector);
			
			//rotate by z axis
			(*rotationVector)[0] = 0.0;
			(*rotationVector)[1] = 0.0;
			(*rotationVector)[2] = 1.0;
			this->setRotation((*rotation)[2], rotationVector);
			
			delete rotationVector;
		}
	}
	
}
void Joint::draw(bool drawMesh) {
	glPushMatrix();
	glTranslatef(originalX + offsetX, originalY + offsetY, originalZ + offsetZ);
	const float color[]= {0.1, 0.5, 1.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glutSolidSphere(0.1,10,10);
	glTranslatef(-1 * (originalX + offsetX), -1 * (originalY + offsetY), -1 * (originalZ + offsetZ));
	
	if ((drawMesh) && (this->mesh != NULL)) {
		this->mesh->draw();
		if (meshConnection != NULL) {
			meshConnection->draw();
		}
	}
	
	for (int i=0;i<childrenNumber;i++) {
			Joint *child = (*children)[i];
			vector<float> coords = child->getCoords();
			glMaterialfv(GL_FRONT, GL_AMBIENT, color);
			glBegin(GL_LINES);
			glVertex3f(originalX + offsetX, originalY + offsetY, originalZ + offsetZ);
			glVertex3f((coords)[0], (coords)[1], (coords)[2]);
			glEnd();
			child->draw(drawMesh);
	}
	glPopMatrix();
}
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