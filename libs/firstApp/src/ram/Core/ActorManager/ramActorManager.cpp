#include "ramActorManager.h"
#include "ramConstants.h"
#include "ramNodeFinder.h"



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
#pragma mark setup, update, draw, exit...
void ramActorManager::setup()
{
	nodeSelector = new NodeSelector(rootNode);
	ofAddListener(nodeSelector->selectStateChanged, this, &ramActorManager::onSelectStateChanged);
	ofAddListener(ofEvents().mouseReleased, this, &ramActorManager::onMouseReleased);
}

void ramActorManager::update()
{
	while (oscReceiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
		ramActorManager::instance().updateWithOscMessage(m);
	}
	
	nodearrays.updateIndexCache();
	
	for (int i = 0; i < nodearrays.size(); i++)
	{
		const ramNodeArray &array = nodearrays[i];
		
		if (array.isOutdated() && !isFreezed() && !array.isPlayback())
		{
			if (array.isActor())
			{
				ramActor o = array;
				ofNotifyEvent(actorExit, o);
			}
			else
			{
				ramRigidBody o = array;
				ofNotifyEvent(rigidExit, o);
			}
			
			nodearrays.erase(array.getName());
		}
	}
	
	rootNode.update();
}

void ramActorManager::draw()
{
	rootNode.draw();
	
	if (nodeSelector != NULL && nodeSelector->identifer.isValid())
	{
		ramNode node;
		ramNodeFinder finder(nodeSelector->identifer);
		
		if (finder.findOne(node))
		{
			node.beginTransform();
			
			ofPushStyle();
			ramBillboard();
			
			ofFill();
			ofSetColor(255, 0, 0, 80);
			ofCircle(0, 0, 10 + sin(ofGetElapsedTimef() * 10) * 5);
			
			ofNoFill();
			ofCircle(0, 0, 10 + sin(ofGetElapsedTimef() * 10) * 5);
			ofPopStyle();
			
			node.endTransform();
		}
	}
}

void ramActorManager::exit()
{
	
}



#pragma mark -
#pragma mark accessor: nodearrays
size_t ramActorManager::getNumNodeArray()
{
	return nodearrays.size();
}

bool ramActorManager::hasNodeArray(const string &key)
{
	return nodearrays.hasKey(key);
}

ramNodeArray& ramActorManager::getNodeArray(const string& name)
{
	return nodearrays[name];
}

ramNodeArray& ramActorManager::getNodeArray(int index)
{
	return nodearrays[index];
}

vector<ramNodeArray*> ramActorManager::getAllNodeArrays()
{
	return nodearrays.all();
}

const vector<string>& ramActorManager::getNodeArrayNames()
{
	return nodearrays.keys();
}


#pragma mark -
#pragma mark !!!:experimental
void ramActorManager::setNodeArray(const ramNodeArray& NA)
{
	nodearrays.set(NA.getName(), NA);
}


#pragma mark -
#pragma mark mouse picked node

const ramNodeIdentifier& ramActorManager::getLastSelectedNodeIdentifer()
{
	return nodeSelector->identifer;
}

const ramNode* ramActorManager::getLastSelectedNode()
{
	const ramNodeIdentifier &node_id = getLastSelectedNodeIdentifer();
	if (!node_id.isValid()) return NULL;
	
	return &getNodeArray(node_id.name).getNode(node_id.index);
}

const ramNodeArray* ramActorManager::getLastSelectedNodeArray()
{
	const ramNodeIdentifier &node_id = getLastSelectedNodeIdentifer();
	if (!node_id.isValid()) return NULL;
	
	return &getNodeArray(node_id.name);
}

void ramActorManager::clearSelected()
{
	nodeSelector->identifer.clear();
}



#pragma mark -
#pragma mark freeze/unfreeze all actors
bool ramActorManager::isFreezed() const
{
	return freeze;
}

void ramActorManager::setFreezed(bool freezed)
{
	freeze = freezed;
}
void ramActorManager::toggleFreeze()
{
	freeze ^= true;
}



#pragma mark -
#pragma mark osc handling
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

void ramActorManager::setupOscReceiver(ramOscManager* oscMan)
{
	oscReceiver.addAddress(RAM_OSC_ADDR_ACTOR);
	oscReceiver.addAddress(RAM_OSC_ADDR_RIGID_BODY);
	
	oscMan->addReceiverTag(&oscReceiver);
}


#pragma mark -
#pragma mark nodeselector
void ramActorManager::onSelectStateChanged(ramNodeIdentifier &e)
{
	ofNotifyEvent(selectStateChanged, e);
}

void ramActorManager::onMouseReleased(ofMouseEventArgs &e)
{
	if (!rootNode.hasFocusdObject())
		nodeSelector->identifer.clear();
}






