#ifndef _BVH_READER_H_
#define _BVH_READER_H_
#include <vector>
#include <iostream>
#include <fstream>

#include "bvhobject.h"
using namespace std;
class BVHReader {
private:
	
	char *filename;
	
	int objectsNumber;
	vector <BVHObject*> *sequence;
	BVHObject *rootObject;
	void doHierarchy(ifstream *datafile);
	void doMotion(ifstream *datafile);
	
	BVHObject *doCreateBVHObject(int level, char *name);
	void doOffset(BVHObject *bvhobject, ifstream *datafile, bool endSite);
	void doChannels(BVHObject *bvhobject, ifstream *datafile);
	
	BVHObject *getParentByLevel(int level, BVHObject *prevObj);
	
	int frames;
	float frameTime;
	
public:
	BVHReader(char *filename);
	void readData();
	vector<BVHObject *> *getSequence();
	int getObjectsNumber();
	int getFrameNumber();
	BVHObject *getRootBVHObject();
};
#endif