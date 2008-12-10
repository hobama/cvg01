#include <string>
#include "bvhreader.h"



/**
 * Constructor
 */
BVHReader::BVHReader(char *filename)
{
	this->filename	= filename;
	this->objectsNumber = 0;
	this->sequence = new vector<BVHObject *>;
	this->rootObject = NULL;
	this->frames = 0;
}

/**
 * Load and read file
 */
void BVHReader::readData()
{
	
	ifstream *datafile = new ifstream(this->filename);
	if (datafile->is_open())
	{
		string line;
		while (!datafile->eof())
		{
			getline (*datafile, line, '\n');
			// Hierarchy
			if(line.compare("HIERARCHY") == 0) {
				doHierarchy(datafile);
			}
			// Animation data
			else if(line.compare("MOTION") == 0) {
				doMotion(datafile);
			}
		}
		datafile->close();
		//
		for (int i=0;i<objectsNumber;i++) {
			BVHObject *bvh = (*sequence)[i];
			bvh->debug();
		}
	} else {
		cout << "Unable to open file";
	}
}

vector<BVHObject *>* BVHReader::getSequence() {
	return this->sequence;
}

int BVHReader::getObjectsNumber() {
	return this->objectsNumber;
}
int BVHReader::getFrameNumber() {
	return this->frames;
}
BVHObject* BVHReader::getRootBVHObject() {
	return this->rootObject;
}
/**
 * Hierachy
 */
void BVHReader::doHierarchy(ifstream *datafile)
{
	string line;
	char * cstr;
	BVHObject *bvhobject, *prevObj, *parent;
	
	bool wasRoot = false; // To do cycle, as we compare bracket count. If it's false, we don't increase brackets count on root.
	int brackets = 1; // Set to 1, because we assume that root already has 1, though we don't add on root.
	bool endSite = false; // If we are in End Site data [needed for end site offset]
	
	while (brackets != 0)
	{
		*datafile >> line;
		// Brackets
		if(line.compare("{") == 0)
		{
			if(wasRoot) {
				brackets++;
			} else {
				wasRoot = true;
			}
		}
		else if(line.compare("}") == 0)
		{
			brackets--;
		}
		// End site
		else if(line.compare("End") == 0)
		{
			endSite = true;
			*datafile >> line; // read unneccessary "Site"
		}
		
		// ROOT/JOINT
		else if(line.compare("ROOT") == 0)
		{
			*datafile >> line;
			cstr = new char [line.size()+1];
			strcpy (cstr, line.c_str());
			bvhobject = doCreateBVHObject(0, cstr);
			this->rootObject = bvhobject;
		}
		else if(line.compare("JOINT") == 0)
		{
			// Assign previouse object
			prevObj = bvhobject;
			*datafile >> line;
			cstr = new char [line.size()+1];
			strcpy (cstr, line.c_str());
			bvhobject = doCreateBVHObject(brackets, cstr);
			
			// Parent might not be previous node, as it can be brother
			parent = getParentByLevel((brackets-1), prevObj);
			parent->addChild(bvhobject);
			bvhobject->setParent(parent);
		}
		// Data
		else if(line.compare("OFFSET") == 0)
		{
			// Do offset function
			doOffset(bvhobject, datafile, endSite);
			if(endSite) endSite = false;
		}
		else if(line.compare("CHANNELS") == 0)
		{
			// Do channels function
			doChannels(bvhobject, datafile);
		}
	}
}

//Create object (root or joint)
BVHObject *BVHReader::doCreateBVHObject(int level, char *name)
{
	BVHObject *bvhobject = new BVHObject(name, level);
	(*this->sequence).push_back(bvhobject);
	this->objectsNumber++;
	return bvhobject;
}

//Create offset data
void BVHReader::doOffset(BVHObject *bvhobject, ifstream *datafile, bool endSite)
{
	float x,y,z;
	
	*datafile >> x;
	*datafile >> y;
	*datafile >> z;
	
	if(!endSite) bvhobject->setOffset(x,y,z);
	else bvhobject->setOffsetEndSite(x,y,z);
	
}

// Create channels and their sequence
void BVHReader::doChannels(BVHObject *bvhobject, ifstream *datafile)
{
	int count;
	*datafile >> count;
	
	if(count > 0) {
		string chan;
		char *cstr;
		bvhobject->setChannelsNumber(count);
		for(int i=0; i<count; i++)
		{
			*datafile >> chan;
			cstr = new char [chan.size()+1];
			strcpy (cstr, chan.c_str());
			bvhobject->addChannel(cstr);
		}
	}
}

/**
 * Motion
 */
void BVHReader::doMotion(ifstream *datafile)
{
	
	// Frame information
	int frames;
	float frameTime;
	string word;
	bool readmore = true;
	
	// Read frames info data
	while (!datafile->eof() && readmore)
		
	{
		*datafile >> word;
		if(word.compare("Frames:") == 0) {
			*datafile >> frames;
		} else if(word.compare("Frame") == 0) {
			*datafile >> word; // skip "time" word
			*datafile >> frameTime;
			readmore = false;
		}
	}
	
	this->frames = frames;
	this->frameTime = frameTime;
	
	// Coordinates info
	float xPos, yPos, zPos, xRot, yRot, zRot;
	int type;
	bool rot = false, pos = false;
	BVHFrame *bvhframe;
	
	// Read coordinates data
	while (!datafile->eof())
		
	{
		for(int i=0; i<(this->sequence->size()); i++)
		{
			rot = false; pos = false;
			
			for (int j=0; j<(*this->sequence)[i]->getChannelsNumber(); j++)
			{
				/**
				 * Legend:
				 * 11 - pos x
				 * 12 - pos y
				 * 13 - pos z
				 * 21 - rot x
				 * 22 - rot y
				 * 23 - rot z
				 */
				type = (*this->sequence)[i]->getChannel(j);
				switch(type) {
					case 11:
						*datafile >> xPos;
						pos = true;
						break;
					case 12:
						*datafile >> yPos;
						break;
					case 13:
						*datafile >> zPos;
						break;
					case 21:
						*datafile >> xRot;
						rot = true;
						break;
					case 22:
						*datafile >> yRot;
						break;
					case 23:
						*datafile >> zRot;
						break;
				}
			}
			
			// insert to frame
			bvhframe = new BVHFrame();
			if(rot) {
				bvhframe->setRot(xRot, yRot, zRot);
			}
			if(pos) {
				bvhframe->setPos(xPos, yPos, zPos);
			}
			(*this->sequence)[i]->addFrame(bvhframe);
		}
		
	}
}



/**
 * Get parent for current object. Parent is the one with level given
 */
BVHObject *BVHReader::getParentByLevel(int level, BVHObject *prevObj)
{
	while(prevObj->getLevel() != level)
	{
		prevObj = prevObj->getParent();
	}
	return prevObj;
}