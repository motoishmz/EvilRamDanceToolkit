#include "ramBaseScene.h"


#pragma mark -
#pragma mark ...
ramBaseScene::ramBaseScene() {}
ramBaseScene::~ramBaseScene() {}
void ramBaseScene::setupControlPanel() {}

#pragma mark -
#pragma mark ...
void ramBaseScene::setup() {}
void ramBaseScene::update() {}
void ramBaseScene::draw() {}
void ramBaseScene::drawActor(const ramActor &actor) {}
void ramBaseScene::drawRigid(const ramRigidBody &rigid) {}
void ramBaseScene::drawHUD() {}
void ramBaseScene::exit() {}

#pragma mark -
#pragma mark ...
void ramBaseScene::onActorEnter(const ramActor &actor) {}
void ramBaseScene::onActorExit(const ramActor &actor) {}
void ramBaseScene::onRigidEnter(const ramRigidBody &rigid) {}
void ramBaseScene::onRigidExit(const ramRigidBody &rigid) {}


//
ramBaseScene* ramBaseScene::getPtr()
{
	return this;
}


