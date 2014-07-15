#include "ramSceneManager.h"
#include "ramActorManager.h"
#include "ramGUI.h"

#ifndef NULL
#define NULL 0
#endif


#pragma mark -
#pragma mark Singleton
ramSceneManager* ramSceneManager::our_instance = NULL;

ramSceneManager& ramSceneManager::instance()
{
	if (our_instance == NULL)
		our_instance = new ramSceneManager;
	return *our_instance;
}



#pragma mark -
#pragma mark private constructors
ramSceneManager::ramSceneManager()
{}
ramSceneManager::ramSceneManager(const ramSceneManager&)
{}
ramSceneManager& ramSceneManager::operator=(const ramSceneManager&)
{ return *this; }



#pragma mark -
#pragma mark setup, update, draw, exit...
void ramSceneManager::setup()
{
	//! driving ramSceneManager::update, draw, exit
	ofAddListener(ofEvents().update, this, &ramSceneManager::update);
	ofAddListener(ofEvents().draw, this, &ramSceneManager::draw);
	ofAddListener(ofEvents().exit, this, &ramSceneManager::exit);
	
	//! listening the entity enter/exit event
	ofAddListener(ramActorManager::instance().actorEnter, this, &ramSceneManager::actorEnter);
	ofAddListener(ramActorManager::instance().actorExit, this, &ramSceneManager::actorExit);
	ofAddListener(ramActorManager::instance().rigidEnter, this, &ramSceneManager::rigidEnter);
	ofAddListener(ramActorManager::instance().rigidExit, this, &ramSceneManager::rigidExit);
}
void ramSceneManager::update(ofEventArgs &e)
{

}
void ramSceneManager::draw(ofEventArgs &e)
{
	
}
void ramSceneManager::exit(ofEventArgs &e)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		scenes[i]->exit();
	}

	ofRemoveListener(ofEvents().update, this, &ramSceneManager::update);
	ofRemoveListener(ofEvents().draw, this, &ramSceneManager::draw);
	ofRemoveListener(ofEvents().exit, this, &ramSceneManager::exit);
	ofRemoveListener(ramActorManager::instance().actorEnter, this, &ramSceneManager::actorEnter);
	ofRemoveListener(ramActorManager::instance().actorExit, this, &ramSceneManager::actorExit);
	ofRemoveListener(ramActorManager::instance().rigidEnter, this, &ramSceneManager::rigidEnter);
	ofRemoveListener(ramActorManager::instance().rigidExit, this, &ramSceneManager::rigidExit);
}


#pragma mark -
#pragma mark entity enter/exit events which are triggerd by ramActorManager
void ramSceneManager::actorEnter(ramActor &actor)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (!scenes[i]->isEnabled())
			scenes[i]->onActorEnter(actor);
	}
}

void ramSceneManager::actorExit(ramActor &actor)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (!scenes[i]->isEnabled())
			scenes[i]->onActorExit(actor);
	}
}

void ramSceneManager::rigidEnter(ramRigidBody &rigid)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (!scenes[i]->isEnabled())
			scenes[i]->onRigidEnter(rigid);
	}
}

void ramSceneManager::rigidExit(ramRigidBody &rigid)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (!scenes[i]->isEnabled())
			scenes[i]->onRigidExit(rigid);
	}
}



#pragma mark -
#pragma mark ...
void ramSceneManager::addScene(ramBaseScene* scene)
{
	scenes.push_back(scene);
	scene->setup();
	ramGUI::instance().addPanel(scene);
}


