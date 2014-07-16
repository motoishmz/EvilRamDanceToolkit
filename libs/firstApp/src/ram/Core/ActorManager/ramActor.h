#pragma once
#include "ramNodeArray.h"

class ramActor : public ramNodeArray
{
	
public:
	
	enum Joint
	{
		JOINT_HIPS              = 0,
		JOINT_ABDOMEN           = 1,
		JOINT_CHEST             = 2,
		JOINT_NECK              = 3,
		JOINT_HEAD              = 4,
		
		JOINT_LEFT_HIP          = 5,
		JOINT_LEFT_KNEE         = 6,
		JOINT_LEFT_ANKLE        = 7,
		JOINT_LEFT_TOE          = 8,
		
		JOINT_RIGHT_HIP         = 9,
		JOINT_RIGHT_KNEE        = 10,
		JOINT_RIGHT_ANKLE       = 11,
		JOINT_RIGHT_TOE         = 12,
		
		JOINT_LEFT_COLLAR       = 13,
		JOINT_LEFT_SHOULDER     = 14,
		JOINT_LEFT_ELBOW        = 15,
		JOINT_LEFT_WRIST        = 16,
		JOINT_LEFT_HAND         = 17,
		
		JOINT_RIGHT_COLLAR      = 18,
		JOINT_RIGHT_SHOULDER    = 19,
		JOINT_RIGHT_ELBOW       = 20,
		JOINT_RIGHT_WRIST       = 21,
		JOINT_RIGHT_HAND        = 22,
		
		NUM_JOINTS              = 23,
	};
	
	
	ramActor();
	ramActor(const ramNodeArray &copy);
	virtual ~ramActor();
	
	//! operator
	ramActor& operator=(const ramNodeArray &copy);
	
	//! utils
	static string getJointName(int jointId) { return jointName[jointId]; }
	static vector<string> getJointNames();
	
private:
	
	static string jointName[NUM_JOINTS];
	
	void dispose();
	
	void setupTree();
};
