#include "ramAccelerometer.h"

ramAccelerometer::ramAccelerometer()
{
	acceleration.set(0, 0, 0);
	angular_velocity.set(0, 0, 0, 1);
	last_pos.set(0, 0, 0);
	last_rot.set(0, 0, 0, 1);
}
ramAccelerometer::~ramAccelerometer()
{}

void ramAccelerometer::update(const ofVec3f &pos, const ofQuaternion &quat)
{
	velocity = last_pos - pos;
	last_pos = pos;
	
	acceleration = last_velocity - velocity;
	last_velocity = velocity;
	
	angular_velocity = last_rot.inverse() * quat;
	last_rot = quat;
	
	angular_acceleration = last_angular_velocity.inverse() * angular_velocity;
	last_angular_velocity = angular_velocity;
}
