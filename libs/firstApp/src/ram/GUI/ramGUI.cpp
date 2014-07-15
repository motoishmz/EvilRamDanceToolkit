#include "ramGUI.h"

#ifndef NULL
#define NULL 0
#endif



#pragma mark -
#pragma mark Sigleton
ramGUI *ramGUI::our_instance = NULL;

ramGUI& ramGUI::instance()
{
	if (our_instance == NULL)
		our_instance = new ramGUI();
	
	return *our_instance;
}



#pragma mark -
#pragma mark private constructors
ramGUI::ramGUI()
: gui_ready(false)
{}
ramGUI::ramGUI(const ramGUI&)
: gui_ready(false)
{}
ramGUI& ramGUI::operator=(const ramGUI&)
{ return *this; }



#pragma mark -
#pragma mark ...
void ramGUI::setup()
{
    gui_tab_bar = new ofxUITabBar();
	gui_panels.clear();
	
	//! ここでdefaultの3枚を追加
	
	for(int i = 0; i < 10; i++)
    {
        string index = ofToString(i);
		
        ofxUICanvas* gui = new ofxUICanvas();
        gui->setName("GUI" + index);
        gui->addLabel("GUI" + index);
        gui->addSpacer();
        gui->addSlider("SLIDER " + index, 0, 1.0, i/10.0);
        gui->add2DPad("PAD " + index, ofVec2f(-1, 1), ofVec2f(-1, 1), ofVec2f(0.0, 0.0));
        gui->autoSizeToFitWidgets();
        gui_tab_bar->addCanvas(gui);
        gui_panels.push_back(gui);
    }
	
	gui_ready = true;
}


void ramGUI::addPanel(ramUnit* unit)
{
	if (!ready())
	{
		ofLogWarning(__FUNCTION__) << "Skipped adding panel because GUI is not ready. Call ramGUI::setup() first.";
		return;
	}
	
	ofxUICanvas* panel = new ofxUICanvas();
	current_panel_context = panel;
	
	unit->setupControlPanel();
	panel->autoSizeToFitWidgets();
	panel->setName(unit->getName());
	
	gui_tab_bar->addCanvas(panel);
	gui_panels.push_back(panel);
}

bool ramGUI::ready()
{
	return gui_ready;
}

ofxUICanvas* ramGUI::getCurrentUIContext()
{
	return current_panel_context;
}