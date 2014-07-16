#include "ramActorManager.h"
#include "ramConstants.h"


#pragma mark -
#pragma mark Singleton
ramActorManager* ramActorManager::our_instance = NULL;

ramActorManager& ramActorManager::instance()
{
	if (our_instance == NULL)
		our_instance = new ramActorManager;
	return *our_instance;
}


#pragma mark -
#pragma mark private constructors
ramActorManager::ramActorManager()
: freeze(false)
{}

ramActorManager::ramActorManager(const ramActorManager&)
{}

ramActorManager& ramActorManager::operator=(const ramActorManager&)
{}



#pragma mark -
#pragma mark updateWithOscMessage!
void ramActorManager::updateWithOscMessage(ofxOscMessage& m)
{
	if (isFreezed()) return;
	
	const std::string addr = m.getAddress();
	const std::string name = m.getArgAsString(0);
	
	if (addr == RAM_OSC_ADDR_ACTOR)
	{
		if (!nodearrays.hasKey(name))
		{
			ramActor o;
			o.setType(RAM_NODEARRAY_TYPE_ACTOR);
			o.setName(name);
			o.updateWithOscMessage(m);
			nodearrays.set(name, o);
			
			ofNotifyEvent(actorEnter, o);
		}
		else
		{
			ramActor &o = (ramActor &)nodearrays[name];
			o.updateWithOscMessage(m);
		}
	}
	else if (addr == RAM_OSC_ADDR_RIGID_BODY)
	{
		if (!nodearrays.hasKey(name))
		{
			ramRigidBody o;
			o.setType(RAM_NODEARRAY_TYPE_RIGIDBODY);
			o.setName(name);
			o.updateWithOscMessage(m);
			nodearrays.set(name, o);
			
			ofNotifyEvent(rigidEnter, o);
		}
		else
		{
			ramRigidBody &o = (ramRigidBody &)nodearrays[name];
			o.updateWithOscMessage(m);
		}
	}
    else
	{
		ofLogError("ramActorManager::updateWithOscMessage") << "received invalid message.";
		assert(false);
	}
}



#pragma mark -
#pragma mark setup, update, draw, exit...
void ramActorManager::setup()
{
//	nodeSelector = new NodeSelector(rootNode);
}

void ramActorManager::update()
{
	
}

void ramActorManager::draw()
{
	
}

void ramActorManager::exit()
{
	
}



#pragma mark -
#pragma mark accessor: nodearrays
inline size_t ramActorManager::getNumNodeArray()
{
	return nodearrays.size();
}

inline vector<ramNodeArray> ramActorManager::getAllNodeArrays()
{
	vector<ramNodeArray> r;
	for (int i = 0; i < getNumNodeArray(); i++)
		r.push_back(getNodeArray(i));
	return r;
}

inline const vector<string>& ramActorManager::getNodeArrayNames()
{
	return nodearrays.keys();
}

inline ramNodeArray& ramActorManager::getNodeArray(int index)
{
	return nodearrays[index];
}

inline ramNodeArray& ramActorManager::getNodeArray(const string& name)
{
	return nodearrays[name];
}

inline bool ramActorManager::hasNodeArray(const string &key)
{
	return nodearrays.hasKey(key);
}











