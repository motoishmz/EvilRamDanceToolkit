#pragma once
#include "ofxXmlSettings.h"
#include "ramCameraSettings.h"

class ramCameraManager
{
	
public:
	
	static ramCameraManager& instance();
	
	void ramBeginCamerea() {}
	void ramEndCamera() {}

	inline size_t getNumCameras() { return cameras.size(); }
	ofCamera* getCamera(size_t index) { return cameras[index]; }
	
	ofCamera& getActiveCamera() { return *active_camera; }
	inline void setActiveCamera(int index) { active_camera = cameras.at(index); }
	
	template <typename T>
	T* createCamera()
	{
		T *o = new T;
		cameras.push_back(o);
		return o;
	}
	
	void setEnableInteractiveCamera(bool v);
	
	// defaults
	void loadDefaults();
	
	vector<string> getDefaultCameraNames();
	void rollbackDefaultCameraSetting(int camera_id = -1);

	
private:
	
	ofCamera *active_camera;
	vector<ofCamera*> cameras;
	
	void update(ofEventArgs& args);
	
	vector<ramCameraSettings> settings;
	
	int last_camera_id;
	
	
	static ramCameraManager *our_instance;
	
	ramCameraManager();
	ramCameraManager(const ramCameraManager &);
	ramCameraManager& operator=(const ramCameraManager&);
};
