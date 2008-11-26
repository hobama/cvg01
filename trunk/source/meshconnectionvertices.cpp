
#include "meshconnectionvertices.h"

const float SUB_VERTICES_COUNT = 4.0;

MeshConnectionVertices::MeshConnectionVertices(float *jointX, float *jointY, float *jointZ) {
	
	this->mainVertices = new vector<Vertex *>(2);
	this->subVertices = new vector<Vertex *>(SUB_VERTICES_COUNT-1);
	
	this->numOfSubVertices = 0;
	this->jointX = jointX;
	this->jointY = jointY;
	this->jointZ = jointZ;
}

void MeshConnectionVertices::setTranslation(float x, float y, float z) {
	(*mainVertices)[0]->setX(x);
	(*mainVertices)[0]->setY(y);
	(*mainVertices)[0]->setZ(z);
	
	(*mainVertices)[1]->setX(x);
	(*mainVertices)[1]->setY(y);
	(*mainVertices)[1]->setZ(z);
	for (int i=0;i<numOfSubVertices;i++) {
		Vertex *vertex = (*subVertices)[i];
		vertex->setX(x);
		vertex->setY(y);
		vertex->setZ(z);
	}
	
}

void MeshConnectionVertices::setVertices(vector<Vertex *> *mainVertices) {
	Vertex *vertex = (*mainVertices)[0];
	(*this->mainVertices)[0] = new Vertex(vertex->getOriginalX(), vertex->getOriginalY(), vertex->getOriginalZ());
	vertex = (*mainVertices)[1];
	(*this->mainVertices)[1] = new Vertex(vertex->getOriginalX(), vertex->getOriginalY(), vertex->getOriginalZ());
	
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
	
	x_f = (*this->mainVertices)[1]->getOriginalX() - (*this->mainVertices)[0]->getOriginalX();
	y_f = (*this->mainVertices)[1]->getOriginalY() - (*this->mainVertices)[0]->getOriginalY();
	z_f = (*this->mainVertices)[1]->getOriginalZ() - (*this->mainVertices)[0]->getOriginalZ();
	
	float t = 1 / SUB_VERTICES_COUNT;
	
	for(int i=1; i < SUB_VERTICES_COUNT; i++) {
		
		x_t = (*this->mainVertices)[0]->getOriginalX() + i*t*x_f;
		y_t = (*this->mainVertices)[0]->getOriginalY() + i*t*y_f;
		z_t = (*this->mainVertices)[0]->getOriginalZ() + i*t*z_f;
		
		(*this->subVertices)[this->numOfSubVertices++] = new Vertex(x_t, y_t, z_t);
	}
}

void MeshConnectionVertices::rotate(float angle, vector<float> *rotationVector) {
	/**
	 * Spheres
	 */
	angle = angle / (this->numOfSubVertices + 1);
	float rotationAngle = 0.0;
	for(int i=0; i < this->numOfSubVertices; i++) {
		Vertex *subVertex = (*subVertices)[i];
		if ((angle != 0) && (rotationVector != NULL)) {
			rotationAngle += angle;
			subVertex->rotateVertex(rotationAngle, rotationVector, *jointX, *jointY, *jointZ);
		}
	}
	
	
	
	Vertex *vertex;
	
	vertex = (*this->mainVertices)[1];
	//update the child position after rotation as well;
	if ((angle != 0) && (rotationVector != NULL)) {
		rotationAngle += angle;
		vertex->rotateVertex(rotationAngle, rotationVector, *jointX, *jointY, *jointZ);
	}

}
void MeshConnectionVertices::setRotation(float **rotationMatrix, float jointX, float jointY, float jointZ) {
	Vertex *vertex;
	vertex = (*this->mainVertices)[0];
	vertex->setRotation(rotationMatrix, jointX, jointY, jointZ);
	vertex = (*this->mainVertices)[1];
	vertex->setRotation(rotationMatrix, jointX, jointY, jointZ);
	
	for (int i=0;i<numOfSubVertices;i++) {
		vertex = (*subVertices)[i];
		vertex->setRotation(rotationMatrix, jointX, jointY, jointZ);
	}
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
		Vertex *subVertex = (*subVertices)[i];
		glTranslatef(subVertex->getOriginalX() + subVertex->getX(), subVertex->getOriginalY() + subVertex->getY(), subVertex->getOriginalZ() + subVertex->getZ());
		glutSolidSphere(0.01,10,10);
		glPopMatrix();
	}
	
	glPopMatrix();	
}

