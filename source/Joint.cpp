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
	
	this->directionX = 0.0;
	this->directionY = 0.0;
	this->directionZ = 0.0;
	this->angle = 0.0;
	//animation
	this->frames = NULL;	
	this->rotationSequence = NULL;
	
	total = new Quaternion();
}

/*
 * Set parent
 */
void Joint::setParent(Joint *parent) {
	this->parent = parent;
}

Joint* Joint::getParent() {
	return this->parent;
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
void Joint::setFrames(vector<BVHFrame *> *bvhFrames) {
	this->frames = new vector<Frame *>(bvhFrames->size());
	for (int i=0;i<frames->size();i++) {
		total->resetToInitial();
		BVHFrame *bvhFrame = (*bvhFrames)[i];
		vector<float> *rotation = bvhFrame->getRot();
		if (rotationSequence != NULL) {
			for (int i=rotationSequence->size() - 1;i>=0;i--) {
			//for (int i=0;i<rotationSequence->size();i++) {
				Quaternion *temp;
				char rotationType = (*rotationSequence)[i];
				switch(rotationType){
					case 'X':
						temp = new Quaternion((*rotation)[0], 1.0, 0.0, 0.0);
						//temp->normalize();
						total->multiply(temp);
						break;
					case 'Y':
						temp = new Quaternion((*rotation)[1], 0.0, 1.0, 0.0);
						//temp->normalize();
						total->multiply(temp);
						break;
					case 'Z':
						temp = new Quaternion((*rotation)[2], 0.0, 0.0, 1.0);
						//temp->normalize();
						total->multiply(temp);
						break;
				}
				delete temp;
			}
		}
		vector<float> *pos = bvhFrame->getPos();
		Frame *frame = new Frame(total->getAngle(), total->getVectorX(), total->getVectorY(), total->getVectorZ());
		if (pos != NULL) 
			frame->setPos(pos);
		(*frames)[i] = frame;
	}
	delete bvhFrames;
}

vector<Frame *>* Joint::getFrames() {
	return this->frames;
}

void Joint::setMesh(Mesh *mesh) {
	this->mesh = mesh;
}

void Joint::createMeshConnection() {
	float distanceDeviation = 0.2;
	if (this->parent != NULL) {
		if ((this->mesh != NULL) && (parent->getMesh() != NULL)) {
			if (strcmp(this->name, "Chest") == 0)
				distanceDeviation = 0.1;
			if (strcmp(this->name, "Chest2") == 0)
				distanceDeviation = 0.4;
			if (strcmp(this->name, "LeftShoulder") == 0)
				distanceDeviation = 0.4;
			if (strcmp(this->name, "RightShoulder") == 0)
				distanceDeviation = 0.55;
			if (strcmp(this->name, "LeftHip") == 0)
				distanceDeviation = 0.36;
			if (strcmp(this->name, "RightHip") == 0)
				distanceDeviation = 0.36;
			this->meshConnection = new MeshConnection(this->mesh, parent->getMesh(), distanceDeviation);
			this->meshConnection->connectVertices(this->x, this->y, this->z);
		}
	}
}
Mesh* Joint::getMesh() {
	return this->mesh;
}

float Joint::getX() {
	return this->x;
}
float Joint::getY() {
	return this->y;
}
float Joint::getZ() {
	return this->z;
}
void Joint::setX(float x) {
	this->x = x;
}
void Joint::setY(float y){
	this->y = y;
}
void Joint::setZ(float z) {
	this->z = z;
}
void Joint::setRotationSequence(vector<char> *rotationSequence) {
	this->rotationSequence = rotationSequence;
	//cout<<this->name<<": "<<(*rotationSequence)[0]<<(*rotationSequence)[1]<<(*rotationSequence)[2]<<endl;
}
void Joint::setTranslation(float x, float y, float z) {
	float diffX = x - this->x;
	float diffY = y - this->y;
	float diffZ = z - this->z;
	this->x = x;
	this->y = y;
	this->z = z;
	
	//translate the mesh
	if (this->mesh != NULL)
		mesh->addTranslation(diffX, diffY, diffZ);
	
	//translate mesh connection
	if (this->meshConnection != NULL)
		meshConnection->addTranslation(diffX, diffY, diffZ);
	
	//do translation for children as well
	for (int i=0;i<childrenNumber;i++) {
		Joint *joint = (*children)[i];
		joint->addTranslation(diffX, diffY, diffZ);
	}
	
}
void Joint::addTranslation(float x, float y, float z) {
	this->x = this->x + x;
	this->y = this->y + y;
	this->z = this->z + z;
	
	//translate the mesh
	if (this->mesh != NULL)
		mesh->addTranslation(x, y, z);
	
	//translate mesh connection
	if (this->meshConnection != NULL) {
		meshConnection->addTranslation(x, y, z);
	}
	//do translation for children as well
	for (int i=0;i<childrenNumber;i++) {
		Joint *joint = (*children)[i];
		joint->addTranslation(x, y, z);
	}
}
void Joint::updateFrame(int frameNumber) {
	if (frames != NULL) {
		Frame *frame = (*frames)[frameNumber];
		this->directionX = frame->getDirectionX();
		this->directionY = frame->getDirectionY();
		this->directionZ = frame->getDirectionZ();
		this->angle = frame->getAngle();
		if (this->angle > 180) {
			this->directionX *= -1;
			this->directionY *= -1;
			this->directionZ *= -1;
			this->angle = 360 - this->angle;
		}
		vector<float> *pos = frame->getPos();
		if ((strcmp(this->name,"Hips") == 0) && (pos != NULL)) {
			this->setTranslation((*pos)[0], (*pos)[1], (*pos)[2]);
		}
		if ((strcmp(this->name, "LeftCollar") == 0) || (strcmp(this->name,"RightCollar") == 0)) {
			this->angle = 0.0;
		}
		if (meshConnection != NULL) {
			meshConnection->resetRotation();
			meshConnection->rotate(angle, directionX, directionY, directionZ);
		}
		
	}
}

void Joint::draw(bool drawMesh) {
	glPushMatrix();
	
	if (meshConnection != NULL && drawMesh)
		meshConnection->draw(); 
	
	glTranslatef(x, y, z);
	const float color[]= {0.1, 0.5, 1.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glutSolidSphere(0.1,10,10);
	glRotatef(angle, directionX, directionY, directionZ);
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
