#pragma once
#include "ofVec3f.h"
#include "ofQuaternion.h"

class ramAccelerometer
{
	friend class ramNode;
	
public:
	ramAccelerometer();
	virtual ~ramAccelerometer();
	
	void update(const ofVec3f &pos, const ofQuaternion &quat);
	
private:
	ofVec3f
		velocity,
		last_velocity,
		acceleration;
	
	ofQuaternion
		angular_velocity,
		last_angular_velocity,
		angular_acceleration;
	
	ofVec3f last_pos;
	ofQuaternion last_rot;
};
