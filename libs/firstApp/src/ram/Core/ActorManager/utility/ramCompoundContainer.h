#pragma once

#include "ramNodeArray.h"

class ramCompoundContainer
{
	
	typedef std::map<string, ramNodeArray> MapType;
	typedef vector<ramNodeArray*> ArrayType;
	
public:
	
	void set(const string &key, const ramNodeArray &o);
	void erase(const string &key);
	void clear();
	size_t size();
	
	//! array
	ramNodeArray& operator[](size_t index);
	const vector<ramNodeArray*> all();
	
	//! map
	ramNodeArray& operator[](const string& key);
	const vector<string>& keys();
	bool hasKey(const string& key);
	
	void updateIndexCache();
	
private:
	
	MapType hash;
	ArrayType array;
	
	vector<string> hash_keys;
};