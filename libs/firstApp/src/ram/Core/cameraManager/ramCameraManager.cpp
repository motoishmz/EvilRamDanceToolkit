#include "ramCameraManager.h"
#include "ramGlobalShortcuts.h"

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
{
	last_camera_id = 0;
	
	active_camera = createCamera<ofEasyCam>();
	
	loadDefaults();
	
	ofAddListener(ofEvents().update, this, &ramCameraManager::update);
}
ramCameraManager::ramCameraManager(const ramCameraManager &)
{}
ramCameraManager& ramCameraManager::operator=(const ramCameraManager&)
{ return *this; }


#pragma mark -
#pragma mark ...
void ramCameraManager::loadDefaults()
{
	const string &kCamSettingFile = ramToResourcePath("Settings/camera/cam.default_positions.xml");
	ofxXmlSettings xml(kCamSettingFile);
	settings = ramCameraSettings::loadSettings(xml);
}

vector<string> ramCameraManager::getDefaultCameraNames()
{
	vector<string> names;
	for (int i = 0; i < settings.size(); i++)
	{
		names.push_back(settings[i].name);
	}
	return names;
}

void ramCameraManager::setEnableInteractiveCamera(bool v)
{
	if (typeid(*active_camera) == typeid(ofEasyCam))
	{
		ofEasyCam *cam = (ofEasyCam*)active_camera;
		
		if (v) cam->enableMouseInput();
		else cam->disableMouseInput();
	}
}

void ramCameraManager::rollbackDefaultCameraSetting(int camera_id)
{
	if(camera_id == -1) camera_id = last_camera_id;
	const ramCameraSettings &setting = settings.at(camera_id);
	active_camera->setPosition(setting.pos);
	active_camera->lookAt(setting.look_at);
	active_camera->setFov(setting.fov);
	last_camera_id = camera_id;
}

void ramCameraManager::update(ofEventArgs& args)
{
	if (typeid(*active_camera) == typeid(ofEasyCam))
	{
		ofEasyCam *cam = (ofEasyCam*)active_camera;
		ofVec3f position = cam->getPosition();
		ofVec3f basePosition = ofVec3f(0, 0, cam->getDistance());
		if(position == basePosition) {
			rollbackDefaultCameraSetting();
		}
	}
}