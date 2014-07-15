#pragma once

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