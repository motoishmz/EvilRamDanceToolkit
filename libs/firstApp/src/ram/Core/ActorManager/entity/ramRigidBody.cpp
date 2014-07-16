#include "ramRigidBody.h"


#pragma mark -
#pragma mark constructor
ramRigidBody::ramRigidBody()
{
	type = RAM_NODEARRAY_TYPE_ACTOR;
}

#pragma mark -
#pragma mark orverriding ramNodeArray::updateWithOscMessage(...)
void ramRigidBody::updateWithOscMessage(const ofxOscMessage &m)
{
	const int nNodes = m.getArgAsInt32(1);
	
	if (nNodes != getNumNode())
		reserveNodes(nNodes);
	
	ramNodeArray::updateWithOscMessage(m);
}


#pragma mark -
#pragma mark operators
ramRigidBody& ramRigidBody::operator=(const ramNodeArray &copy)
{
	this->ramNodeArray::operator=(copy);
	return *this;
}

#pragma mark -
#pragma mark ...
void ramRigidBody::reserveNodes(int num)
{
	nodes.resize(num);
}
