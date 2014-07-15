#pragma once
#include <vector>
#include "ofEvents.h"
#include "ramBaseScene.h"


class ramSceneManager
{
	
public:
	
	static ramSceneManager& instance();
	
	void setup();
	void addScene(ramBaseScene*);
	
protected:
	
	void update(ofEventArgs &e);
	void draw(ofEventArgs &e);
	void exit(ofEventArgs &e);
	
	void actorEnter(ramActor &actor);
	void actorExit(ramActor &actor);
	void rigidEnter(ramRigidBody &rigid);
	void rigidExit(ramRigidBody &rigid);
	
private:
	
	std::vector<ramBaseScene*> scenes;
	
	static ramSceneManager *our_instance;
	ramSceneManager();
	ramSceneManager(const ramSceneManager&);
	ramSceneManager& operator=(const ramSceneManager&);
};
