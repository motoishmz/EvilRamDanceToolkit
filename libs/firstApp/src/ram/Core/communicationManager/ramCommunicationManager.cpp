#include "ramCommunicationManager.h"

ramCommunicationManager* ramCommunicationManager::__instance = NULL;

ofColor
uiThemecb(128, 192),
uiThemeco(192, 192),
uiThemecoh(192, 192),
uiThemecf(255, 255),
uiThemecfh(160, 255),
uiThemecp(128, 192),
uiThemecpo(255, 192);

void ramCommunicationManager::setup(ramOscManager* oscMan){
	
	UIcanvas.setName("Communicator");
	UIcanvas.disableAppDrawCallback();
	UIcanvas.setUIColors(uiThemecb, uiThemeco, uiThemecoh, uiThemecf, uiThemecfh, uiThemecp, uiThemecpo);
	
	refleshInstruments();
	
	ofAddListener(newGUIEvent, this, &ramCommunicationManager::guiEvent);
	ofAddListener(ofEvents().keyPressed, this, &ramCommunicationManager::keyPressed);
	
	bVisible = true;
	
	oscReceiver.addAddress("/ram/communicate/");
	oscMan->addReceiverTag(&oscReceiver);
}

void ramCommunicationManager::update(){
	
	while (oscReceiver.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
		
		ramCommunicationManager::instance().updateWithOscMessage(m);
	}
	
}

void ramCommunicationManager::draw(){
	if (bVisible) UIcanvas.draw();
}

void ramCommunicationManager::updateWithOscMessage(const ofxOscMessage &m){
	const std::string addr = m.getAddress();
	const std::string name = m.getArgAsString(0);
	
	int index = 0;
	
	bool isExist = false;
	for (int i = 0;i < Instruments.size();i++){
		if (name == Instruments[i]->getName())
		{
			index   = i;
			isExist = true;
		}
	}
	
	if (!isExist) index = addInstrument(name);
	
	
	if (addr == RAM_OSC_ADDR_COMMUNICATE_NOTEON){
		Instruments[index]->getFloat("velocity") = m.getArgAsFloat(1);
		velocities[index]->setValue(m.getArgAsFloat(1));
	}
	
	else if (addr == RAM_OSC_ADDR_COMMUNICATE_NOTEOFF){
		Instruments[index]->getFloat("velocity") = 0.0;
		velocities[index]->setValue(0.0);
	}
	
	else if (addr == RAM_OSC_ADDR_COMMUNICATE_CC){
		int ccNum = m.getNumArgs();
		for (int i = 0;i < ccNum - 1;i++){
			string ccLabel = "cc" + ofToString(i);
			
			if (Instruments[index]->contains(ccLabel))
			{
				
				Instruments[index]->getFloat(ccLabel) = m.getArgAsFloat(i+1);
				ccs[index][i]->setValue(m.getArgAsFloat(i+1));
				
			}
			else
			{
				Instruments[index]->add((*new ofParameter<float>).set(ccLabel,
																	  m.getArgAsFloat(i+1),0.0,1.0));
				refleshInstruments();
			}
			
		}
		
	}
	
}

int ramCommunicationManager::addInstrument(string name){
	
	ofParameterGroup* newInst = new ofParameterGroup();
	
	newInst->setName(name);
	newInst->add((*new ofParameter<float>).set("velocity",0.0,0.0,1.0));
	
	Instruments.push_back(newInst);
	
	refleshInstruments();
	
	return Instruments.size() - 1;
}

void ramCommunicationManager::refleshInstruments(){
	
	UIcanvas.removeWidgets();
	UIcanvas.resetPlacer();
	UIcanvas.addSpacer(0,0);
	UIcanvas.addLabel("Communicator");
	
	velocities.clear();
	ccs.clear();
	
	for (int i = 0;i < Instruments.size();i++){
		UIcanvas.addSpacer();
		UIcanvas.addLabel("Instruments"+ofToString(i)+" : "+Instruments[i]->getName(),OFX_UI_FONT_SMALL);
		velocities.push_back(UIcanvas.addSlider("velocity",
												0.0,
												1.0,
												Instruments[i]->getFloat("velocity")));
		
		vector<ofxUISlider*> cc;
		ccs.push_back(cc);
		
		for (int j = 0;j < 4;j++){
			if (Instruments[i]->contains("cc"+ofToString(j))){
				ccs[i].push_back(UIcanvas.addSlider("cc"+ofToString(j),
													0.0,
													1.0,
													0.0));
			}
		}
	}
	
	UIcanvas.setPosition(ofGetWidth()-UIcanvas.getRect()->getWidth(), 0.0);
	UIcanvas.autoSizeToFitWidgets();
}

float ramCommunicationManager::getVelocity(string name){
	int index = 0;
	for (int i = 0;i < Instruments.size();i++){
		if (name == Instruments[i]->getName())
			index = i;
	}
	
	return getVelocity(index);
}

float ramCommunicationManager::getVelocity(int index){
	if ((Instruments.size() == 0) || (index >= Instruments.size()))
		return 0.0;
	
	return Instruments[index]->getFloat("velocity");
}

float ramCommunicationManager::getCC(string name, int ccNum){
	int index = 0;
	for (int i = 0;i < Instruments.size();i++){
		if (name == Instruments[i]->getName())
			index = i;
	}
	
	return getCC(index,ccNum);
}

float ramCommunicationManager::getCC(int index, int ccNum){
	if ((Instruments.size() == 0) || (index >= Instruments.size()))
		return 0.0;
	
	if (Instruments[index]->contains("cc"+ofToString(ccNum)))
		return Instruments[index]->getFloat("cc"+ofToString(ccNum));
	
	return 0.0;
}

void ramCommunicationManager::guiEvent(ofxUIEventArgs &e){
	
}

void ramCommunicationManager::keyPressed(ofKeyEventArgs &key){
	if (key.key == OF_KEY_TAB) bVisible ^= true;
}