#pragma once
#include "ofEvents.h"
#include "ofxOscMessage.h"
#include "ramOscManager.h"
#include "ramCompoundContainer.h"
#include "ramActor.h"
#include "ramRigidBody.h"
#include "ramInteractivePrimitive.h"
#include "ramNodeIdentifier.h"

class ramActorManager
{
	
public:
	
	static ramActorManager& instance();
	
	ofEvent<ramActor> actorEnter;
	ofEvent<ramActor> actorExit;
	ofEvent<ramRigidBody> rigidEnter;
	ofEvent<ramRigidBody> rigidExit;
	ofEvent<ramNodeIdentifier> selectStateChanged;
	
	void setup();
	void update();
	void draw();
	void exit();

	
	size_t getNumNodeArray();
	bool hasNodeArray(const string &key);
	ramNodeArray& getNodeArray(int index);
	ramNodeArray& getNodeArray(const string& name);
	vector<ramNodeArray*> getAllNodeArrays();
	const vector<string>& getNodeArrayNames();
	
	
	// 
	void setNodeArray(const ramNodeArray& NA);
	
	
	// for mouse picked node
	const ramNodeIdentifier& getLastSelectedNodeIdentifer();
	const ramNode* getLastSelectedNode();
	const ramNodeArray* getLastSelectedNodeArray();
	void clearSelected();
	
	
	//! freeze/unfreeze all actors
	bool isFreezed() const;
	void setFreezed(bool freezed);
	void toggleFreeze();
	
private:
	
	ramCompoundContainer nodearrays;
	
	bool freeze;
	
	
	/*!
	 osc
	 */
	ramOscReceiveTag oscReceiver;
	void setupOscReceiver(ramOscManager* oscMan);
	void updateWithOscMessage(ofxOscMessage& m);
	
	
	/*!
	 nodeselector
	 */
	class NodeSelector;
	friend class NodeSelector;
	NodeSelector *nodeSelector;
	ramInteractivePrimitives::RootNode rootNode;
	
	void onSelectStateChanged(ramNodeIdentifier &e);
	void onMouseReleased(ofMouseEventArgs &e);


	
	/*!
	 noncopiable
	 */
	static ramActorManager *our_instance;
	ramActorManager();
	ramActorManager(const ramActorManager&);
	ramActorManager& operator=(const ramActorManager&);
};



#pragma mark -
#pragma mark implementation ramActorManager::NodeSelector
#include "ramNodeSelector.h"