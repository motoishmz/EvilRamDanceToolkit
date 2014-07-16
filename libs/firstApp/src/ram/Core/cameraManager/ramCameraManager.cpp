#include "ramCameraManager.h"

#ifndef NULL
#define NULL 0
#endif

#pragma mark -
#pragma mark Sigleton
ramCameraManager* ramCameraManager::our_instance = NULL;

ramCameraManager& ramCameraManager::instance()
{
	if (our_instance == NULL)
		our_instance = new ramCameraManager();
	
	return *our_instance;
}



#pragma mark -
#pragma mark private constructors

ramCameraManager::ramCameraManager()
{}
ramCameraManager::ramCameraManager(const ramCameraManager &)
{}
ramCameraManager& ramCameraManager::operator=(const ramCameraManager&)
{ return *this; }