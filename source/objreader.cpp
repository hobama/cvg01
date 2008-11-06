/*
 *  objreader.cpp
 *  objloader
 *
 *  Created by a1gucis on 10/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#include "objreader.h"

const int INITIAL_VECTOR_SIZE = 200;
const float VECTOR_GROWTH = 0.5;
const int POLYGON_SIZE = 3;

ObjReader::ObjReader(char *filename) {
	numOfTexels = 0;
	numOfVertices = 0;
	numOfNormals = 0;
	numOfPolygons = 0;
	vertices = new vector<Vertex *>(INITIAL_VECTOR_SIZE);
	texels = new vector<Texel *>(INITIAL_VECTOR_SIZE);
	normals = new vector<Normal *>(INITIAL_VECTOR_SIZE);
	polygons = new vector<Polygon3 *>(INITIAL_VECTOR_SIZE);
	this->filename	= filename;
}

void ObjReader::readData() {
	ifstream *datafile = new ifstream(filename);
	
	if (datafile->is_open())
	{
		char controlSymbol;
		char buffer[1024];
		int line = 0;
		while (!datafile->eof()) {
			*datafile >> controlSymbol;
			switch (controlSymbol) {
				case 'v': //vertex data
					readVertexData(datafile);
					break;
				case 'f': //polygon data
					readPolygonData(datafile);
					break;
				default:
					datafile->getline(buffer, 1024);
					break;
			}
		}
		datafile->close();
	}else 
		cout << "Unable to open file";
}

void ObjReader::readVertexData(ifstream *datafile) {
	char controlSymbol; 
	float x, y, z;
	controlSymbol = datafile->peek();
	switch (controlSymbol) {
		case 't': //it is a texel
			*datafile >> controlSymbol;
			*datafile >> x;
			*datafile >> y;
			Texel *texel = new Texel(x, y);
			if (numOfTexels == texels->size()) {
				int newsize = floor(texels->size() + texels->size() * VECTOR_GROWTH);
				texels->resize(newsize);
			}
			(*texels)[numOfTexels++] = texel;
			break;
		case 'n':// it is normal
			*datafile >> controlSymbol;
			
			*datafile >> x;
			*datafile >> y;
			*datafile >> z;
			Normal *normal = new Normal(x, y, z);
			if (numOfNormals == normals->size()) {
				int newsize = floor(normals->size() + normals->size() * VECTOR_GROWTH);
				normals->resize(newsize);
			}
			(*normals)[numOfNormals++] = normal;
			break;
		case 'p':
			
			break;
		default: //it is a vertex
			*datafile >> x;
			*datafile >> y;
			*datafile >> z;
			Vertex *vertex = new Vertex(x, y, z);
			if (numOfVertices == vertices->size()) {// need to increase the size of our vector
				int newsize = floor(vertices->size() + vertices->size() * VECTOR_GROWTH);
				vertices->resize(newsize);
			}
 			(*vertices)[numOfVertices++] = vertex;
			
			break;
	}
}

void ObjReader::readPolygonData(ifstream *datafile) {
	//vector<float> *pVertices;
	vector<Vertex *> *tVertices = new vector<Vertex *>(POLYGON_SIZE);
	vector<Texel*> *tTexels = new vector<Texel *>(POLYGON_SIZE);
	vector<Normal *> *tNormals = new vector <Normal *>(POLYGON_SIZE);
	int vertexIndex, texelIndex, normalIndex;
	char separator;
	for (int i=0;i<POLYGON_SIZE;i++) {
		//reading vertex info
		*datafile >> vertexIndex;
		(*tVertices)[i] = (*vertices)[vertexIndex - 1];
		*datafile >> separator;
		
		//reading texel info
		if (datafile->peek() != '/') {
			*datafile >> texelIndex;
			(*tTexels)[i] = (*texels)[texelIndex - 1];
			//cout <<i<<": texelIndex:"<<texelIndex<<endl;
			*datafile >> separator;

		} else
			*datafile >> separator;
		
		//reading normal info
		*datafile >> normalIndex;
		(*tNormals)[i] = (*normals)[normalIndex - 1];

	}
	Polygon3 *polygon3 = new Polygon3(tVertices, tTexels, tNormals);
	if (numOfPolygons == polygons->size()) {
		int newSize = floor(polygons->size() + polygons->size()*VECTOR_GROWTH);
		polygons->resize(newSize);
	}
	(*polygons)[numOfPolygons++] = polygon3;
}

vector<Polygon3 *> *ObjReader::getPolygons() {
	return polygons;
}

int ObjReader::getNumOfPolygons() {
	return numOfPolygons;
}
//#####################
vector<Vertex *> *ObjReader::getVertices() {
	return vertices;
}

vector<Normal *> *ObjReader::getNormals() {
	return normals;
}

vector<Texel *> *ObjReader::getTexels() {
	return texels;
}


void ObjReader::displayVertexData() {
	for (int i=0;i<numOfVertices;i++) {
		Vertex *vertex = (*vertices)[i];
		cout <<"v "<<vertex->getX()<<" "<<vertex->getY()<<" "<<vertex->getZ()<<endl;
	}
}
void ObjReader::displayNormalData() {
	for (int i=0;i<numOfNormals;i++) {
		Normal *vertex = (*normals)[i];
		cout <<"vn "<<vertex->getX()<<" "<<vertex->getY()<<" "<<vertex->getZ()<<endl;
	}
	
}
void ObjReader::displayTexelData() {
	for (int i=0;i<numOfTexels;i++) {
		Texel *vertex = (*texels)[i];
		cout <<"vt "<<vertex->getX()<<" "<<vertex->getY()<<" "<<vertex->getZ()<<endl;
	}
	
}