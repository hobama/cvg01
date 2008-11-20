#ifndef _BVH_FRAME_H_
#define _BVH_FRAME_H_
#include <vector>
using namespace std;

class BVHFrame {
private:

	vector<float> *pos;
	vector<float> *rot;
public:
	BVHFrame(void);

	void setPos(float x, float y, float z);
	void setRot(float x, float y, float z);

	vector<float> *getPos() { return this->pos; }
	vector<float> *getRot() { return this->rot; }

};
#endif