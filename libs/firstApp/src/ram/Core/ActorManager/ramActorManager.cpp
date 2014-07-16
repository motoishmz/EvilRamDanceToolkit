#include "ramActorManager.h"

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
#pragma mark updateWithOscMessage!
void ramActorManager::updateWithOscMessage(ofxOscMessage& m)
{
	
}


#pragma mark -
#pragma mark setup, update, draw...
void ramActorManager::setup()
{
	
}
void ramActorManager::update(ofEventArgs &e)
{
	
}
void ramActorManager::draw(ofEventArgs &e)
{
	
}
void ramActorManager::exit(ofEventArgs &e)
{
	
}