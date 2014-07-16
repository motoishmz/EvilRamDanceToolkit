#pragma once
#include "ofEvents.h"
#include "ofxOscMessage.h"
#include "ramActor.h"
#include "ramRigidBody.h"
#include "ramInteractivePrimitive.h"
#include "ramNodeIdentifier.h"
#include "ramCompoundContainer.h"



class ramActorManager
{
	
public:
	
	static ramActorManager& instance();
	
	ofEvent<ramActor> actorEnter;
	ofEvent<ramActor> actorExit;
	ofEvent<ramRigidBody> rigidEnter;
	ofEvent<ramRigidBody> rigidExit;
	ofEvent<ramNodeIdentifier> selectStateChanged;
	
	void updateWithOscMessage(ofxOscMessage& m);
	
	void setup();
	void update();
	void draw();
	void exit();

	
	size_t getNumNodeArray();
	vector<ramNodeArray> getAllNodeArrays();
	const vector<string>& getNodeArrayNames();
	ramNodeArray& getNodeArray(int index);
	ramNodeArray& getNodeArray(const string& name);
	bool hasNodeArray(const string &key);
	
	
	// test
	void setNodeArray(const ramNodeArray& NA) { nodearrays.set(NA.getName(), NA); }
	
	
	// for mouse picked node
	const ramNodeIdentifier& getLastSelectedNodeIdentifer();
	const ramNode* getLastSelectedNode();
	const ramNodeArray* getLastSelectedNodeArray();
	void clearSelected();
	
	// Freeze all actor
	inline bool isFreezed() { return freeze; }
	inline void setFreezed(bool v) { freeze = v; }
	inline void toggleFreeze() { freeze ^= true; }

	
	
	
private:
	
	ramCompoundContainer nodearrays;
	
	bool freeze;
	
	
	/*!
	 nodeselector
	 */
	class NodeSelector;
	friend class NodeSelector;
	NodeSelector *nodeSelector;
	void onSelectStateChanged(ramNodeIdentifier &e);
	void onMouseReleased(ofMouseEventArgs &e);
	ramInteractivePrimitives::RootNode rootNode;


	
	/*!
	 noncopiable
	 */
	static ramActorManager *our_instance;
	ramActorManager();
	ramActorManager(const ramActorManager&);
	ramActorManager& operator=(const ramActorManager&);
};




