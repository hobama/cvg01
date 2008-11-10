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

		/*Debug - print full tree
		for (int i=0;i<numOfJoints;i++) {
			(*joints)[i]->debugJoint();
		}*/
	}else 
		cout << "Unable to open file";
}

/*
 * Read joint data
 */
void JointReader::readJointData(ifstream *datafile) {
	char controlSymbol; 
	float x, y, z;
	char *name=NULL;

	controlSymbol = datafile->peek();

	switch (controlSymbol) {
		case 'c': //If it's a joint hierarchy list
			{
				*datafile >> controlSymbol;

				// Get joint
				Joint *curjoint = NULL;
				name = new char[JOINT_NAME_SIZE];
				*datafile >> name;
				curjoint = this->findJointByName(name);
				//cout << "========" << endl;
				//cout << "n: " << name << endl;
				if(curjoint) {
					// Set parent joint
					char *parname = new char[JOINT_NAME_SIZE];
					*datafile >> parname;
					if(strcmp("0", parname) != 0) {
						Joint *pppjoint = this->findJointByName(parname);
						curjoint->setParent(pppjoint);
					}
					//cout << "p: " << parname << endl;
					// Get child count
					int childcount;
					*datafile >> childcount;

					// Set childs
					for (int i=0;i<childcount;i++) {
						char *childname = new char[JOINT_NAME_SIZE];
						*datafile >> childname;
						cout << name << " -> " << childname << endl;
						curjoint->addChild(this->findJointByName(childname));
						
					}
				}
				//cout << "========" << endl;
			}
			break;
		default: //If it's a new joint
			{
			// Joint name
			name = new char[JOINT_NAME_SIZE];
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

	string n1, n2;
	n1 = name;

	for (int i=0;i<numOfJoints;i++) {
		n2 = (*joints)[i]->getName();
		if (n1 == n2) 
		{
			Joint *joint = (*joints)[i];
			return joint;
		}

	}
	return NULL;
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