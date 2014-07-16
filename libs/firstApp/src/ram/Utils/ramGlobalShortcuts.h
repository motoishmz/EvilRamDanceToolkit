#pragma once

#include "ramGUI.h"
#include "ramSceneManager.h"
#include "ramActorManager.h"
#include "ramCameraManager.h"
#include "ramOscManager.h"
#include "ramCommunicationManager.h"

#pragma mark -
#pragma mark Shortcut to access singleton instances

//! shortcut to GUI
static ramGUI& ramGetGUI()
{
	return (ramGUI &) ramGUI::instance();
}

//! shortcut to ramSceneManager
static ramSceneManager& ramGetSceneManager()
{
	return (ramSceneManager &) ramSceneManager::instance();
}


//! shortcut to ramActorManager
static ramActorManager& ramGetActorManager()
{
	return (ramActorManager &) ramActorManager::instance();
}

//! shortcut to ramCommunicationManager
static ramCameraManager& ramGetCameraManager()
{
	return ramCameraManager::instance();
}

//! shortcut to ramCommunicationManager
static ramOscManager& ramGetOscManager()
{
	return ramOscManager::instance();
}

//! shortcut to ramCommunicationManager
static ramCommunicationManager& ramGetCommunicationManager()
{
	return ramCommunicationManager::instance();
}


#pragma mark -
#pragma mark ActorManager
size_t getNumNodeArray();
bool hasNodeArray(string key);
ramNodeArray& getNodeArray(string name);
ramNodeArray& getNodeArray(int index);
vector<ramNodeArray*> getAllNodeArrays();


#pragma mark -
#pragma mark CameraManager
void ramBeginCamera();
void ramEndCamera();



#pragma mark -
#pragma mark physics
void ramEnablePhysicsPrimitive(bool v = true);
void ramDisablePhysicsPrimitive();
bool ramGetEnablePhysicsPrimitive();



#pragma mark -
#pragma mark shadows
void ramEnableShadow(bool v = true);
void ramDisableShadow();
bool ramShadowEnabled();

void ramBeginShadow();
void ramEndShadow();
void ramSetShadowAlpha(float alpha);