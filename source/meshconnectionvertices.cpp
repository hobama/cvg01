
#include "meshconnectionvertices.h"

const float SUB_VERTICES_COUNT = 4.0;

MeshConnectionVertices::MeshConnectionVertices(float jointX, float jointY, float jointZ) {
	
	this->mainVertices = new vector<Vertex *>(2);
	this->subVertices = new vector<Vertex *>(SUB_VERTICES_COUNT-1);
	
	this->numOfSubVertices = 0;
	this->jointX = jointX;
	this->jointY = jointY;
	this->jointZ = jointZ;
	rotated = false;
}



void MeshConnectionVertices::setVertices(vector<Vertex *> *mainVertices) {
	Vertex *vertex = (*mainVertices)[0];
	(*this->mainVertices)[0] = new Vertex(vertex->getX(), vertex->getY(), vertex->getZ());
	vertex = (*mainVertices)[1];
	(*this->mainVertices)[1] = new Vertex(vertex->getX(), vertex->getY(), vertex->getZ());
	
	this->setSubVertices();
}

vector<Vertex *>* MeshConnectionVertices::getVertices(){
	vector<Vertex *> *vertices = new vector<Vertex*>(this->numOfSubVertices + 2);
	(*vertices)[0] = (*mainVertices)[0];
	for (int i=0;i<numOfSubVertices;i++) {
		(*vertices)[i+1] = (*subVertices)[i]; 
	}
	
	(*vertices)[this->numOfSubVertices + 1] = (*mainVertices)[1];
	return vertices;
}
void MeshConnectionVertices::setSubVertices() {
	
	float x_f, y_f, z_f, x_t, y_t, z_t;
	
	x_f = (*this->mainVertices)[1]->getX() - (*this->mainVertices)[0]->getX();
	y_f = (*this->mainVertices)[1]->getY() - (*this->mainVertices)[0]->getY();
	z_f = (*this->mainVertices)[1]->getZ() - (*this->mainVertices)[0]->getZ();
	
	float t = 1 / SUB_VERTICES_COUNT;
	
	for(int i=1; i < SUB_VERTICES_COUNT; i++) {
		
		x_t = (*this->mainVertices)[0]->getX() + i*t*x_f;
		y_t = (*this->mainVertices)[0]->getY() + i*t*y_f;
		z_t = (*this->mainVertices)[0]->getZ() + i*t*z_f;
		
		(*this->subVertices)[this->numOfSubVertices++] = new Vertex(x_t, y_t, z_t);
	}
}

void MeshConnectionVertices::updatePos(float angle, vector<float> *rotationVector) {
	/**
	 * Spheres
	 */
	angle = angle / (this->numOfSubVertices + 1);
	float rotationAngle = 0.0;
	for(int i=0; i < this->numOfSubVertices; i++) {
		Vertex *subVertex = (*subVertices)[i];
		if ((angle != 0) && (rotationVector != NULL) && !rotated) {
			subVertex->setX(subVertex->getX() - jointX);
			subVertex->setY(subVertex->getY() - jointY);
			subVertex->setZ(subVertex->getZ() - jointZ);
			rotationAngle += angle;
			vector<float> *position = subVertex->rotateVertex(rotationAngle, rotationVector);
			subVertex->setX((*position)[0] + jointX);
			subVertex->setY((*position)[1] + jointY);
			subVertex->setZ((*position)[2] + jointZ);
		}
	}
	
	
	
	Vertex *vertex;
	
	vertex = (*this->mainVertices)[1];
	//update the child position after rotation as well;
	if ((angle != 0) && (rotationVector != NULL) && !rotated) {
		vertex->setX(vertex->getX() - jointX);
		vertex->setY(vertex->getY() - jointY);
		vertex->setZ(vertex->getZ() - jointZ);
		rotationAngle += angle;
		vector<float> *position = vertex->rotateVertex(rotationAngle, rotationVector);
		vertex->setX((*position)[0] + jointX);
		vertex->setY((*position)[1] + jointY);
		vertex->setZ((*position)[2] + jointZ);
	}
	rotated = true;
}
void MeshConnectionVertices::draw() {
	/**
	 * Spheres
	 */
	glPushMatrix();
	const float colorSphere[]= {0.1, 0.1, 0.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, colorSphere);
	
	for(int i=0; i < this->numOfSubVertices; i++) {
		glPushMatrix();
		glTranslatef((*this->subVertices)[i]->getX(), (*this->subVertices)[i]->getY(), (*this->subVertices)[i]->getZ());
		glutSolidSphere(0.01,10,10);
		glPopMatrix();
	}
	
	glPopMatrix();	
}

