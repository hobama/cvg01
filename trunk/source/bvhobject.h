#ifndef _BVH_OBJECT_H_
#define _BVH_OBJECT_H_
#include <vector>
#include <iostream>
#include "bvhframe.h"

using namespace std;
//using std::vector;

class BVHObject {
private:
	
	char *name;
	
	vector<float> *offset; //x,y,z
	vector<float> *offsetEndSite;
	
	int channelsNumber;
	vector<char *> *channelsOrder;
	
	int childrenNumber;
	vector <BVHObject*> *children;
	BVHObject *parent;
	
	int objectLevel; // To determine what level this object is (root is 0, and every child is more than 0)
	
	//Frame list
	vector <BVHFrame*> *frames;
	/*int frames;
	 float frameTime;
	 void setFrameInfo(int frames, float frameTime);*/
	
public:
	BVHObject(char *name, int objectLevel);
	
	char *getName(void);
	
	void addChild (BVHObject *child);
	void setParent (BVHObject *parent);
	BVHObject *getParent (void);
	
	vector<float> *getOffset();
	vector<float> *getOffsetEndSite();
	void setOffset(float x, float y, float z);
	void setOffsetEndSite(float x, float y, float z);
	
	void setChannelsNumber(int channelsNumber);
	int getChannelsNumber(void);
	void addChannel(char* channel);
	int getChannel(int i);
	
	int getChildrenNumber();
	vector<BVHObject *> *getChildren();
	int getLevel() { return objectLevel; }
	
	void addFrame(BVHFrame *bvhframe);
	vector<BVHFrame *>* getFrames();
	void debug();
};
#endif