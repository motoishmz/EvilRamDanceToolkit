#include "ramBaseFilter.h"
#include "ofUtils.h"

const ramNodeArray& ramBaseFilter::operator()(const ramNodeArray& src)
{
	return update(src);
}

const ramNodeArray& ramBaseFilter::update(const ramNodeArray& src)
{
	if (cache.getNumNode() != src.getNumNode())
		cache = src;
	
	const int f = ofGetFrameNum();
	if (last_update_frame != f)
	{
		last_update_frame = f;
		cache = filter(src);
	}
	
	return cache;
}

const ramNodeArray& ramBaseFilter::get(size_t index) const { return cache; }
size_t ramBaseFilter::getSize() const { return 1; }