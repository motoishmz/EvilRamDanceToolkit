#pragma once
#include "ofxUI.h"
#include "ramOscManager.h"
#include "ramConstants.h"

class ramCommunicationManager
{
public:
	
	void setup(ramOscManager* oscMan);
	void update();
	void draw();
	
	float getVelocity(string name);
	float getVelocity(int index);
	float getCC(string name,int ccNum);
	float getCC(int index,int ccNum);
	
	ofxUICanvas* getCanvas(){return &UIcanvas;};
	
	inline static ramCommunicationManager& instance()
	{
		if (__instance == NULL)
			__instance = new ramCommunicationManager;
		return* __instance;
	};
	
private:
	int addInstrument(string name);
	static ramCommunicationManager *__instance;
	
	ramCommunicationManager() {};
	ramCommunicationManager(const ramCommunicationManager&){}
	ramCommunicationManager& operator=(const ramCommunicationManager&) {return *this; }
	~ramCommunicationManager() {};
	
	bool bVisible;
	
	//Gui
	void						refleshInstruments();
	vector<ofParameterGroup*>	Instruments;
	
	vector<ofxUISlider*>			velocities;
	vector<vector<ofxUISlider*> >	ccs;
	ofxUICanvas						UIcanvas;
	
	//OSC
	ramOscReceiveTag	oscReceiver;
	void			updateWithOscMessage(const ofxOscMessage &m);
	
	ofEvent<ofxUIEventArgs> newGUIEvent;
	void guiEvent(ofxUIEventArgs &e);
	void keyPressed(ofKeyEventArgs &key);
};

