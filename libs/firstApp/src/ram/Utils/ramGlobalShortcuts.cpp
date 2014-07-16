#include "ramGlobalShortcuts.h"


bool hasNodeArray(string key)
{
	return ramGetActorManager().hasNodeArray(key);
}
ramNodeArray& getNodeArray(string name)
{
	return ramGetActorManager().getNodeArray(name);
}
size_t getNumNodeArray()
{
	return ramGetActorManager().getNumNodeArray();
}

ramNodeArray& getNodeArray(int index)
{
	return ramGetActorManager().getNodeArray(index);
}

vector<ramNodeArray*> getAllNodeArrays()
{
	return ramGetActorManager().getAllNodeArrays();
}