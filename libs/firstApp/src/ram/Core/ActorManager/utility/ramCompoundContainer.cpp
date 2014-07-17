#include "ramCompoundContainer.h"


#pragma mark -
#pragma mark ...

template <typename T>
void ramCompoundContainer<T>::set(const string &key, const T &o)
{
	hash[key] = o;
	updateIndexCache();
}

template <typename T>
void ramCompoundContainer<T>::erase(const string &key)
{
	hash.erase(key);
	updateIndexCache();
}

template <typename T>
void ramCompoundContainer<T>::clear()
{
	array.clear();
	hash.clear();
	hash_keys.clear();
}

template <typename T>
size_t ramCompoundContainer<T>::size()
{
	return array.size();
}


#pragma mark -
#pragma mark array

template <typename T>
T& ramCompoundContainer<T>::operator[](size_t index)
{
	return *array[index];
}

template <typename T>
const vector<T*> ramCompoundContainer<T>::all()
{
	return array;
}


#pragma mark -
#pragma mark map
template <typename T>
T& ramCompoundContainer<T>::operator[](const string& key)
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

template <typename T>
const vector<string>& ramCompoundContainer<T>::keys()
{
	return hash_keys;
}

template <typename T>
bool ramCompoundContainer<T>::hasKey(const string& key)
{
	return hash.find(key) != hash.end();
}


#pragma mark -
#pragma mark ...
template <typename T>
void ramCompoundContainer<T>::updateIndexCache()
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
