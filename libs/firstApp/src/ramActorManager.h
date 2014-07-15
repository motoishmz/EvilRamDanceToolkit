#pragma once
#include "ofEvents.h"

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

private:
	
	static ramActorManager *our_instance;
	ramActorManager();
	ramActorManager(const ramActorManager&);
	ramActorManager& operator=(const ramActorManager&);
};

