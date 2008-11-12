
#include "meshconnectionvertices.h"

const float SUB_VERTICES_COUNT = 4.0;

MeshConnectionVertices::MeshConnectionVertices() {

	this->mainVertices = new vector<Vertex *>(2);
	this->subVertices = new vector<Vertex *>(SUB_VERTICES_COUNT-1);

	this->numOfSubVertices = 0;
}



void MeshConnectionVertices::setVertices(vector<Vertex *> *mainVertices) {
	this->mainVertices = mainVertices;

	this->setSubVertices();
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


void MeshConnectionVertices::draw() {

	
	/**
	 * Spheres
	 */
	
	const float colorSphere[]= {0.1, 0.1, 0.6, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, colorSphere);

	for(int i=0; i < this->numOfSubVertices; i++) {
		glPushMatrix();

		glTranslatef((*this->subVertices)[i]->getX(), (*this->subVertices)[i]->getY(), (*this->subVertices)[i]->getZ());
		glutSolidSphere(0.01,10,10);

		glPopMatrix();
	}
	

	glPushMatrix();
	const float color[]= {1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	Vertex *vertex1, *vertex2;

	vertex1 = (*this->mainVertices)[0];
	vertex2 = (*this->mainVertices)[1];

	/**
	 * Lines
	 */
	//vector<Vertex *> *linePointVertices = new vector<Vertex *>(SUB_VERTICES_COUNT+1);
	//linePointVertices[0] = (*this->mainVertices)[0];
	//linePointVertices->push_back((*this->subVertices));
	//linePointVertices->push_back((*this->mainVertices)[1]);

	glBegin(GL_LINES);
	glVertex3f(vertex1->getX(), vertex1->getY(), vertex1->getZ());
	glVertex3f((*this->subVertices).front()->getX(), (*this->subVertices).front()->getY(), (*this->subVertices).front()->getZ());
	glEnd();

	for(int i=0; i < this->numOfSubVertices-1; i++) {
			
		glBegin(GL_LINES);
		glVertex3f((*this->subVertices)[i]->getX(), (*this->subVertices)[i]->getY(), (*this->subVertices)[i]->getZ());
		glVertex3f((*this->subVertices)[i+1]->getX(), (*this->subVertices)[i+1]->getY(), (*this->subVertices)[i+1]->getZ());
			glEnd();
	}

	glBegin(GL_LINES);
	glVertex3f((*this->subVertices).back()->getX(), (*this->subVertices).back()->getY(), (*this->subVertices).back()->getZ());
	glVertex3f(vertex2->getX(), vertex2->getY(), vertex2->getZ());
	glEnd();
	
	glPopMatrix();
}

