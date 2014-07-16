#pragma once



const std::string RAM_OSC_ADDR_ACTOR = "/ram/skeleton";
const std::string RAM_OSC_ADDR_RIGID_BODY = "/ram/rigid_body";

const std::string RAM_OSC_ADDR_COMMUNICATE_NOTEON = "/ram/communicate/noteon";
const std::string RAM_OSC_ADDR_COMMUNICATE_NOTEOFF = "/ram/communicate/noteoff";
const std::string RAM_OSC_ADDR_COMMUNICATE_CC = "/ram/communicate/cc";

const float RAM_OUTDATED_DURATION = 1.0;

typedef enum
{
	RAM_NODEARRAY_TYPE_ACTOR     = 0,
	RAM_NODEARRAY_TYPE_RIGIDBODY = 1
} ramNodeArrayType;

const string jointName[] =
{
	
	"HIPS",
	"ABDOMEN",
	"CHEST",
	"NECK",
	"HEAD",
	"LEFT_HIP",
	"LEFT_KNEE",
	"LEFT_ANKLE",
	"LEFT_TOE",
	"RIGHT_HIP",
	"RIGHT_KNEE",
	"RIGHT_ANKLE",
	"RIGHT_TOE",
	"LEFT_COLLAR",
	"LEFT_SHOULDER",
	"LEFT_ELBOW",
	"LEFT_WRIST",
	"LEFT_HAND",
	"RIGHT_COLLAR",
	"RIGHT_SHOULDER",
	"RIGHT_ELBOW",
	"RIGHT_WRIST",
	"RIGHT_HAND"
};
