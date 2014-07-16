#include "ramNodeFinder.h"
#include "ramNodeIdentifier.h"

#pragma mark -
#pragma mark constructors
ramNodeFinder::ramNodeFinder()
: ramNodeIdentifier()
{}

ramNodeFinder::ramNodeFinder(const ramNodeIdentifier& copy)
: ramNodeIdentifier(copy)
{}

void ramNodeFinder::setTargetName(string name)
{
	this->name = name;
}
void ramNodeFinder::setJointID(int index_)
{
	this->index = index;
}

bool ramNodeFinder::found()
{
	if (!hasNodeArray(name))
		return false;
	
	return index == -1
	|| (index >= 0 && index < getNodeArray(name).getNumNode());
}

bool ramNodeFinder::findOne(ramNode &node)
{
	if (!isValid()) return false;
	
	if (!hasNodeArray(name))
	{
		if (getNumNodeArray() > 0)
		{
			node = getNodeArray(0).getNode(index);
			return true;
		}
		return false;
	}
	else
	{
		node = getNodeArray(name).getNode(index);
		return true;
	}
}

vector<ramNode*> ramNodeFinder::findAll()
{
	vector<ramNode*> nodes;
	
	bool has_target_actor = !name.empty();
	bool has_target_node = index != -1;
	
	for (int i = 0; i < getNumNodeArray(); i++)
	{
		ramNodeArray &actor = getNodeArray(i);
		
		if (has_target_actor && name != actor.getName()) continue;
		
		for (int n = 0; n < actor.getNumNode(); n++)
		{
			if (has_target_node && index != n) continue;
			
			ramNode &node = actor.getNode(n);
			nodes.push_back(&node);
		}
	}
	
	return nodes;
}
