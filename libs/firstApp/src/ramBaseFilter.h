#pragma once
#include "ramUnit.h"
#include "ramActor.h"



class ramBaseFilter : public ramUnit
{
public:
	const ramNodeArray& operator()(const ramNodeArray& src);
	const ramNodeArray& update(const ramNodeArray& src);
	virtual const ramNodeArray& get(size_t index = 0) const;
	virtual size_t getSize() const;
	
protected:
	ramNodeArray cache;
	virtual const ramNodeArray& filter(const ramNodeArray& src) = 0;
	
private:
	int last_update_frame;
};