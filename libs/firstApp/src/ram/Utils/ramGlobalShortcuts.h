#pragma once

#include "ramGUI.h"
#include "ramSceneManager.h"
#include "ramActorManager.h"

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

#pragma mark -
#pragma mark ActorManager
size_t getNumNodeArray();
bool hasNodeArray(string key);
ramNodeArray& getNodeArray(string name);
ramNodeArray& getNodeArray(int index);
vector<ramNodeArray*> getAllNodeArrays();