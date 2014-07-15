#pragma once
#include "ofxUI.h"
#include "ramUnit.h"

class ramGUI
{
	
public:
	static ramGUI &instance();
	
	void setup();
	void addPanel(ramUnit* unit);
	
	bool ready();
	
	ofxUICanvas* getCurrentUIContext();
	
protected:
	
    ofxUITabBar *gui_tab_bar;
    vector<ofxUICanvas *> gui_panels;
	
private:
	static ramGUI *our_instance;
	ramGUI();
	ramGUI(const ramGUI &other);
	ramGUI &operator=(const ramGUI &other);
	
	bool gui_ready;
	ofxUICanvas* current_panel_context;
};
