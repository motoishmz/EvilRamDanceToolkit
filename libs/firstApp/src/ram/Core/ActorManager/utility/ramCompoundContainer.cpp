#include "ramCompoundContainer.h"


#pragma mark -
#pragma mark ...
void ramCompoundContainer::set(const string &key, const ramNodeArray &o)
{
	hash[key] = o;
	updateIndexCache();
}

void ramCompoundContainer::erase(const string &key)
{
	hash.erase(key);
	updateIndexCache();
}

void ramCompoundContainer::clear()
{
	array.clear();
	hash.clear();
	hash_keys.clear();
}

size_t ramCompoundContainer::size()
{
	return array.size();
}


#pragma mark -
#pragma mark array

ramNodeArray& ramCompoundContainer::operator[](size_t index)
{
	return *array[index];
}

const vector<ramNodeArray*> ramCompoundContainer::all()
{
	return array;
}


#pragma mark -
#pragma mark map
ramNodeArray& ramCompoundContainer::operator[](const string& key)
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

const vector<string>& ramCompoundContainer::keys()
{
	return hash_keys;
}

bool ramCompoundContainer::hasKey(const string& key)
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
