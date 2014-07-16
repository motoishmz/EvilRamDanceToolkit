#pragma once
#include "ramNode.h"
#include "ramNodeIdentifier.h"
#include "ramGlobalShortcuts.h"

class ramNodeFinder :  public ramNodeIdentifier
{
public:
	
	ramNodeFinder();
	ramNodeFinder(const ramNodeIdentifier& copy);
	
	void setTargetName(string name);
	void setJointID(int index);
	
	bool found();
	bool findOne(ramNode &node);
	vector<ramNode*> findAll();
};