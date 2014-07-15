#include "ramUnit.h"



ramUnit::ramUnit()
: enabled(false)
{}

ramUnit::~ramUnit() {}
void ramUnit::setupControlPanel() {}

void ramUnit::enable() {enabled = true;}
void ramUnit::disable() {enabled = false;}
void ramUnit::toggle() {setEnabled(!isEnabled());}
bool ramUnit::isEnabled() const {return enabled;}

void ramUnit::setEnabled(bool value)
{
	if (enabled == value) return;
	
	enabled = value;
	
	if (enabled)
		onEnabled();
	else
		onDisabled();
}

void ramUnit::loadPreset(size_t preset_id)
{
	std::cout << "[loadPreset] " << getName() << std::endl;
}

void ramUnit::loadPresetXML(std::string filePath)
{
	std::cout << "[loadPresetXML] " << getName() << std::endl;
}

void ramUnit::onEnabled()
{
	std::cout << "[Unit enabled] " << getName() << std::endl;
}

void ramUnit::onDisabled()
{
	std::cout << "[Unit disabled] " << getName() << std::endl;
}