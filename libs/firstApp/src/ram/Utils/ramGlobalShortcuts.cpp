#include "ramGlobalShortcuts.h"
#include "ramSimpleShadow.h"


static ramSimpleShadow ram_simple_shadow;


#pragma mark -
#pragma mark ActorManager

bool hasNodeArray(string key)
{
	return ramGetActorManager().hasNodeArray(key);
}
ramNodeArray& getNodeArray(string name)
{
	return ramGetActorManager().getNodeArray(name);
}
size_t getNumNodeArray()
{
	return ramGetActorManager().getNumNodeArray();
}

ramNodeArray& getNodeArray(int index)
{
	return ramGetActorManager().getNodeArray(index);
}

vector<ramNodeArray*> getAllNodeArrays()
{
	return ramGetActorManager().getAllNodeArrays();
}




#pragma mark -
#pragma mark CameraManager
void ramBeginCamera()
{}

void ramEndCamera()
{}


#pragma mark -
#pragma mark physics
static bool ram_enable_physics_primitive = true;

void ramEnablePhysicsPrimitive(bool v)
{
	ram_enable_physics_primitive = v;
}

void ramDisablePhysicsPrimitive()
{
	ram_enable_physics_primitive = false;
}

bool ramGetEnablePhysicsPrimitive()
{
	return ram_enable_physics_primitive;
}



#pragma mark -
#pragma mark shadows
void ramEnableShadow(bool v)
{
	ram_simple_shadow.setEnable(v);
}

void ramDisableShadow()
{
	ram_simple_shadow.setEnable(false);
}

bool ramShadowEnabled()
{
	return ram_simple_shadow.getEnable();
}

void ramBeginShadow()
{
	ram_simple_shadow.begin();
}

void ramEndShadow()
{
	ram_simple_shadow.end();
}

void ramSetShadowAlpha(float alpha)
{
	ram_simple_shadow.setShadowAlpha(alpha);
}