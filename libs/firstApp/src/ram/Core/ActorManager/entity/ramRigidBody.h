#pragma once
#include "ramNodeArray.h"

class ramRigidBody : public ramNodeArray
{
	
public:
	
	ramRigidBody();
	ramRigidBody(const ramNodeArray &copy) { *this = copy; }
	
	ramRigidBody& operator=(const ramNodeArray &copy);
	
	virtual void updateWithOscMessage(const ofxOscMessage &m);
	
private:
	
	void reserveNodes(int num);

};
