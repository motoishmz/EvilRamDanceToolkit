#pragma once

#include "ramNodeArray.h"

template <typename T>
class ramCompoundContainer
{
	
	typedef std::map<string, T> MapType;
	typedef vector<T*> ArrayType;
	
public:
	
	void set(const string &key, const T &o);
	void erase(const string &key);
	void clear();
	size_t size();
	
	//! array
	T& operator[](size_t index);
	const vector<T*> all();
	
	//! map
	T& operator[](const string& key);
	const vector<string>& keys();
	bool hasKey(const string& key);
	
	void updateIndexCache();
	
private:
	
	MapType hash;
	ArrayType array;
	
	vector<string> hash_keys;
};