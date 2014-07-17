#include "ramBaseApp.h"


// !!!:
bool drawModel = true;


#pragma mark -
#pragma mark constructor
ramBaseApp::ramBaseApp()
{
	ofAddListener(ramGetActorManager().actorEnter, this, &ramBaseApp::actorSetup);
	ofAddListener(ramGetActorManager().actorExit, this, &ramBaseApp::actorExit);
	ofAddListener(ramGetActorManager().rigidEnter, this, &ramBaseApp::rigidSetup);
	ofAddListener(ramGetActorManager().rigidExit, this, &ramBaseApp::rigidExit);
}

ramBaseApp::~ramBaseApp()
{
	ofRemoveListener(ramGetActorManager().actorEnter, this, &ramBaseApp::actorSetup);
	ofRemoveListener(ramGetActorManager().actorExit, this, &ramBaseApp::actorExit);
	ofRemoveListener(ramGetActorManager().rigidEnter, this, &ramBaseApp::rigidSetup);
	ofRemoveListener(ramGetActorManager().rigidExit, this, &ramBaseApp::rigidExit);
}




#pragma mark -
#pragma mark update, draw exit...
void ramBaseApp::update(ofEventArgs &args)
{
	ramGetActorManager().update();
	
	ramGetCommunicationManager().update();
	
	ramGetOscManager().update();
	
	update(); // calling testApp(or ofApp)::update()
}

void ramBaseApp::draw(ofEventArgs &args)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glEnable(GL_DEPTH_TEST);
	
	ramBeginCamera();
	
	drawFloor();
	
	ramGetActorManager().draw();
	
	bool enable_physics = ramGetEnablePhysicsPrimitive();
	
	ramEnablePhysicsPrimitive(false);
	
	if (ramShadowEnabled())
	{
		// shadow
		
		ramBeginShadow();
		drawNodeArrays();
		ramEndShadow();
	}
	
	ramEnablePhysicsPrimitive(enable_physics);
	
	if (drawModel)
	{
		// entities
		drawNodeArrays();
	}
	
	ramEndCamera();
	
	glPopAttrib();
	
	ramGetCommunicationManager().draw();
	
	draw(); // calling testApp(or ofApp)::draw()
}
void ramBaseApp::exit(ofEventArgs &args)
{
	ofSetFullscreen(false);
}



#pragma mark -
#pragma mark drawing helpers
void ramBaseApp::drawNodeArrays()
{
	// draw nodearray
	
	for (int n = 0; n < getNumNodeArray(); n++)
	{
		const ramNodeArray &o = getNodeArray(n);
		
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		ofPushStyle();
		if (o.isActor())
			drawActor((ramActor &)o);
		else
			drawRigid((ramRigidBody &)o);
		
		ofPopStyle();
		glPopMatrix();
		glPopAttrib();
	}
}

void ramBaseApp::drawFloor()
{
	// !!!:
	cout << ".";
	
//	ramDrawBasicFloor(ramGetGUI().getPreferencesTab().getFloorPattern(),
//					  ramGetGUI().getPreferencesTab().getFloorSize(),
//					  ramGetGUI().getPreferencesTab().getFloorGridSize(),
//					  ramColor::GRAY_ALPHA,
//					  ramColor::DARK_GRAY_ALPHA);
}
