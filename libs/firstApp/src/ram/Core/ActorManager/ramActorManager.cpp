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