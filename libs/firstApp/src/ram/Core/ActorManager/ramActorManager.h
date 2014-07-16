#pragma once
#include "ofEvents.h"
#include "ofxOscMessage.h"

class ramActor;
class ramRigidBody;

class ramActorManager
{
	
public:
	
	static ramActorManager& instance();
	
	ofEvent<ramActor> actorEnter;
	ofEvent<ramActor> actorExit;
	ofEvent<ramRigidBody> rigidEnter;
	ofEvent<ramRigidBody> rigidExit;
	
	void updateWithOscMessage(ofxOscMessage& m);
	
	void setup();

private:
	
	void update(ofEventArgs &e);
	void draw(ofEventArgs &e);
	void exit(ofEventArgs &e);
	
	static ramActorManager *our_instance;
	ramActorManager();
	ramActorManager(const ramActorManager&);
	ramActorManager& operator=(const ramActorManager&);
};

