#include <string>
#include "jointreader.h"


/**
 * Constructor
 */
JointReader::JointReader(char *filename) {
	this->filename	= filename;

	this->numOfJoints = 0;

	joints = new vector<Joint *>;
}

/**
 * Read joint data
 */
void JointReader::readData() {
	ifstream *datafile = new ifstream(this->filename);
	
	if (datafile->is_open())
	{
		char controlSymbol;
		char buffer[1024];
		int line = 0;
		while (!datafile->eof()) {
			*datafile >> controlSymbol;
			
			switch (controlSymbol) {
				case 'j': //joint data
					readJointData(datafile);
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

/*
 * Read joint data
 */
void JointReader::readJointData(ifstream *datafile) {
	char controlSymbol; 
	float x, y, z;
	char name[20];

	controlSymbol = datafile->peek();

	switch (controlSymbol) {
		case 'c': //If it's a joint hierarchy list
			/*{
			*datafile >> controlSymbol;
			*datafile >> x;
			*datafile >> y;
			Texel *texel = new Texel(x, y);
			if (numOfTexels == texels->size()) {
				int newsize = floor(texels->size() + texels->size() * VECTOR_GROWTH);
				texels->resize(newsize);
			}
			(*texels)[numOfTexels++] = texel;
			}*/
			{
			char* name2 = "Asdasd";
			this->findJointByName(name2);
			}
			break;
		default: //If it's a new joint
			{
			// Joint name
			*datafile >> name;
			// Joint positions
			*datafile >> x;
			*datafile >> y;
			*datafile >> z;

			Joint *joint = new Joint(name, x, y, z);

			joints->resize(numOfJoints+1);
			(*joints)[numOfJoints++] = joint;
			}
			break;
	}
}

/**
 * Find joint by its name
 */
Joint *JointReader::findJointByName(char *name) {

	for (int i=0;i<numOfJoints;i++) {

		cout << name <<" - "<<(*joints)[i]->getName() <<endl;
	}
	return (*joints)[1];
}

/**
 * Get full list of joints
 */

vector<Joint *> *JointReader::getJoints() {
	return this->joints;
}

int JointReader::getNumOfJoints() {
	return this->joints->size();
}