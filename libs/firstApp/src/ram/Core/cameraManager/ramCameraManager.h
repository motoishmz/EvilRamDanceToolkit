#pragma once

class ramCameraManager
{
	
public:
	
	static ramCameraManager& instance();
	
	void ramBeginCamerea() {}
	void ramEndCamera() {}

private:
	
	static ramCameraManager *our_instance;
	
	ramCameraManager();
	ramCameraManager(const ramCameraManager &);
	ramCameraManager& operator=(const ramCameraManager&);
};

