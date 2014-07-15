#pragma once
#include <iostream>
#include "ramUnit.h"
#include "ramActor.h"


class ramBaseScene : public ramUnit
{
	
public:
	
	ramBaseScene();
	virtual ~ramBaseScene();
	virtual std::string getName() const = 0;
	virtual void setupControlPanel();
	
	virtual void setup();
	virtual void update();
	virtual void draw();
	virtual void drawHUD();
	virtual void exit();
	virtual void drawActor(const ramActor &actor);
	virtual void drawRigid(const ramRigidBody &rigid);
	
	// nodeArray events
	virtual void onActorEnter(const ramActor &actor);
	virtual void onActorExit(const ramActor &actor);
	virtual void onRigidEnter(const ramRigidBody &rigid);
	virtual void onRigidExit(const ramRigidBody &rigid);
	
	ramBaseScene* getPtr();
};