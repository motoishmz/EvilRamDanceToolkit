#pragma once
#include <iostream>

class ramUnit
{
	
public:
	
	ramUnit();
	virtual ~ramUnit();
	virtual std::string getName() const = 0;
	virtual void setupControlPanel();
	
	void enable();
	void disable();
	void toggle();
	bool isEnabled() const;
	void setEnabled(bool value);
	
	virtual void loadPreset(size_t preset_id = 0);
	virtual void loadPresetXML(std::string filePath);
	virtual void onEnabled();
	virtual void onDisabled();
	
protected:
	
	bool enabled;
};