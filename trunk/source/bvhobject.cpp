#include "bvhobject.h"

/**
 * Constructor
 */
BVHObject::BVHObject(char *name, int objectLevel) {
	
	//assign
	this->name = name;
	
	this->objectLevel = objectLevel;
	
	//init
	this->childrenNumber = 0;
	
	this->channelsOrder = new vector<char *>;
	this->children = new vector<BVHObject *>;
	this->offset = new vector<float>(3);
	this->offsetEndSite = NULL;
	
	this->frames = new vector<BVHFrame*>;
}


/*
 * Set parent
 */
void BVHObject::setParent(BVHObject *parent) {
	this->parent = parent;
}

/*
 * Get parent
 */
BVHObject *BVHObject::getParent() {
	return this->parent;
}

/**
 * Add a new child.
 * Also increase children number.
 */
void BVHObject::addChild (BVHObject *child) {
	
	this->children->resize(this->childrenNumber+1);
	(*this->children)[this->childrenNumber++] = child;
}

/**
 * Get object name
 */
char *BVHObject::getName () {
	return this->name;
}

vector<float>* BVHObject::getOffset() {
	return this->offset;
}
vector<float>* BVHObject::getOffsetEndSite() {
	return this->offsetEndSite;
}
/**
 * Set offset positions
 */
void BVHObject::setOffset(float x, float y, float z) {
	
	//this->offset->resize(3);
	
	(*this->offset)[0] = x;
	(*this->offset)[1] = y;
	(*this->offset)[2] = z;
}

void BVHObject::setOffsetEndSite(float x, float y, float z) {
	
	//this->offsetEndSite->resize(3);
	this->offsetEndSite = new vector<float>(3);
	(*this->offsetEndSite)[0] = x;
	(*this->offsetEndSite)[1] = y;
	(*this->offsetEndSite)[2] = z;
}

/**
 * Set how many channels there will be for this object
 * Example: 6 -> Xposition Yposition Zposition Zrotation Xrotation Yrotation
 */
void BVHObject::setChannelsNumber(int channelsNumber) {
	this->channelsNumber = channelsNumber;
}

int BVHObject::getChannelsNumber() {
	return this->channelsNumber;
}

int BVHObject::getChildrenNumber() {
	return this->childrenNumber;
}

vector <BVHObject *>* BVHObject::getChildren() {
	return this->children;
}
/**
 * Set channel names and their sequence
 */
void BVHObject::addChannel(char* channel) {
	
	(*this->channelsOrder).push_back(channel);
	
}

/**
 * Get type of channel. Legend:
 * 11 - pos x
 * 12 - pos y
 * 13 - pos z
 * 21 - rot x
 * 22 - rot y
 * 23 - rot z
 */
int BVHObject::getChannel(int i) {
	int ret = 0;
	char coord, type;
	
	coord = (*this->channelsOrder)[i][0];
	type = (*this->channelsOrder)[i][1];
	
	switch(type) {
			
		case 'p':
		{
			switch(coord) {
				case 'X':
					ret = 11;
					break;
					
				case 'Y':
					ret = 12;
					break;
					
				case 'Z':
					ret = 13;
					break;
			}
		}
			break;
			
		case 'r':
		{
			switch(coord) {
				case 'X':
					ret = 21;
					break;
					
				case 'Y':
					ret = 22;
					break;
					
				case 'Z':
					ret = 23;
					break;
			}
		}
			break;
	}
	
	return ret;
}

/**
 * Set frame info
 */
//void BVHObject::setFrameInfo(int frames, float frameTime) {
//	this->frames = frames;
//	this->frameTime = frameTime;
//}

void BVHObject::addFrame(BVHFrame *bvhframe) {
	this->frames->push_back(bvhframe);
}

vector<BVHFrame *>* BVHObject::getFrames() {
	return this->frames;
}
void BVHObject::debug() {
	cout<<this->name<<" "<<(*offset)[0]<<" "<<(*offset)[1]<<" "<<(*offset)[2]<<endl;
}