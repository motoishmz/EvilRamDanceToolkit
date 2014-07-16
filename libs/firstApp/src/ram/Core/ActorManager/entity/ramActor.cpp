#include "ramActor.h"


#pragma mark -
#pragma mark constructors
ramActor::ramActor()
{
	type = RAM_NODEARRAY_TYPE_ACTOR;
	
	nodes.resize(NUM_JOINTS);
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].node_id = i;
	}
	
	setupTree();
}

ramActor::ramActor(const ramNodeArray &copy)
{
	*this = copy;
}

ramActor::~ramActor()
{
	dispose();
}



//#pragma mark -
//#pragma mark operator
//ramActor& ramActor::operator=(const ramNodeArray &copy)
//{
//	this->ramNodeArray::operator=(copy);
//	return *this;
//}



#pragma mark -
#pragma mark ....
void ramActor::dispose()
{
	nodes.clear();
}

void ramActor::setupTree()
{
	getNode(JOINT_ABDOMEN).setParent(getNode(JOINT_HIPS));
	{
		getNode(JOINT_CHEST).setParent(getNode(JOINT_ABDOMEN));
		{
			getNode(JOINT_NECK).setParent(getNode(JOINT_CHEST));
			{
				getNode(JOINT_HEAD).setParent(getNode(JOINT_NECK));
			}
		}
		getNode(JOINT_LEFT_COLLAR).setParent(getNode(JOINT_CHEST));
		{
			getNode(JOINT_LEFT_SHOULDER).setParent(getNode(JOINT_LEFT_COLLAR));
			{
				getNode(JOINT_LEFT_ELBOW).setParent(getNode(JOINT_LEFT_SHOULDER));
				{
					getNode(JOINT_LEFT_WRIST).setParent(getNode(JOINT_LEFT_ELBOW));
					{
						getNode(JOINT_LEFT_HAND).setParent(getNode(JOINT_LEFT_WRIST));
					}
				}
				
			}
		}
		
		getNode(JOINT_RIGHT_COLLAR).setParent(getNode(JOINT_CHEST));
		{
			getNode(JOINT_RIGHT_SHOULDER).setParent(getNode(JOINT_RIGHT_COLLAR));
			{
				getNode(JOINT_RIGHT_ELBOW).setParent(getNode(JOINT_RIGHT_SHOULDER));
				{
					getNode(JOINT_RIGHT_WRIST).setParent(getNode(JOINT_RIGHT_ELBOW));
					{
						getNode(JOINT_RIGHT_HAND).setParent(getNode(JOINT_RIGHT_WRIST));
					}
				}
			}
		}
	}
	
	getNode(JOINT_LEFT_HIP).setParent(getNode(JOINT_HIPS));
	{
		
		getNode(JOINT_LEFT_KNEE).setParent(getNode(JOINT_LEFT_HIP));
		{
			getNode(JOINT_LEFT_ANKLE).setParent(getNode(JOINT_LEFT_KNEE));
			{
				getNode(JOINT_LEFT_TOE).setParent(getNode(JOINT_LEFT_ANKLE));
			}
		}
	}
	
	getNode(JOINT_RIGHT_HIP).setParent(getNode(JOINT_HIPS));
	{
		getNode(JOINT_RIGHT_KNEE).setParent(getNode(JOINT_RIGHT_HIP));
		{
			getNode(JOINT_RIGHT_ANKLE).setParent(getNode(JOINT_RIGHT_KNEE));
			{
				getNode(JOINT_RIGHT_TOE).setParent(getNode(JOINT_RIGHT_ANKLE));
			}
		}
	}
}



#pragma mark -
#pragma mark static
vector<string> ramActor::getJointNames()
{
	vector<string> names;
	names.clear();
	names.resize(ramActor::NUM_JOINTS);
	
	for (int i = 0; i < names.size(); i++)
		names.at(i) = getJointName(i);
	return names;
}
