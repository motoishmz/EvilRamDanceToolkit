#pragma once
#include "ofBaseApp.h"
#include "ramBaseScene.h"
#include "ramBaseFilter.h"
#include "ramGlobalShortcuts.h"


class ramBaseApp : public ofBaseApp
{
	
public:
	
	ramBaseApp();
	virtual ~ramBaseApp();
	
protected:
	
	virtual void update() {}
	virtual void draw() {}
	virtual void exit() {}
	
	virtual void onActorSetup(const ramActor &actor) {}
	virtual void onActorExit(const ramActor &actor) {}
	virtual void onRigidSetup(const ramRigidBody &rigid) {}
	virtual void onRigidExit(const ramRigidBody &rigid) {}
	
	virtual void drawActor(const ramActor &actor) {}
	virtual void drawRigid(const ramRigidBody &rigid) {}
	
private:
	
	void drawFloor();
	void drawNodeArrays();
	
	void update(ofEventArgs &args);
	void draw(ofEventArgs &args);
	void exit(ofEventArgs &args);
	void actorSetup(ramActor &actor) { onActorSetup(actor); }
	void actorExit(ramActor &actor) { onActorExit(actor); }
	void rigidSetup(ramRigidBody &rigid) { onRigidSetup(rigid); }
	void rigidExit(ramRigidBody &rigid) { onRigidExit(rigid); }
};