#include "ramCompoundContainer.h"


#pragma mark -
#pragma mark ...
inline void ramCompoundContainer::set(const string &key, const ramNodeArray &o)
{
	hash[key] = o;
	updateIndexCache();
}

inline void ramCompoundContainer::erase(const string &key)
{
	hash.erase(key);
	updateIndexCache();
}

inline void ramCompoundContainer::clear()
{
	array.clear();
	hash.clear();
	hash_keys.clear();
}

inline size_t ramCompoundContainer::size()
{
	return array.size();
}

#pragma mark -
#pragma mark array

inline ramNodeArray& ramCompoundContainer::operator[](size_t index)
{
	return *array[index];
}

const vector<ramNodeArray*> ramCompoundContainer::all()
{
	return array;
}


#pragma mark -
#pragma mark map
inline ramNodeArray& ramCompoundContainer::operator[](const string& key)
{
	if (hasKey(key))
	{
		return hash[key];
	}
	else
	{
		ofLogError("RAMDanceToolkit::ramCompoundContainer") << "invalid key: " << key;
		assert(false);
	}
}

inline const vector<string>& ramCompoundContainer::keys()
{
	return hash_keys;
}

inline bool ramCompoundContainer::hasKey(const string& key)
{
	return hash.find(key) != hash.end();
}


#pragma mark -
#pragma mark ...
void ramCompoundContainer::updateIndexCache()
{
	array.clear();
	hash_keys.clear();
	
	typename MapType::iterator it = hash.begin();
	
	while (it != hash.end())
	{
		hash_keys.push_back(it->first);
		array.push_back(&it->second);
		it++;
	}
}
