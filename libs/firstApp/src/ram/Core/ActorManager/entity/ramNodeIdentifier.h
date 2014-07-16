#pragma once
#include <iostream>

struct ramNodeIdentifier
{
	std::string name;
	int index;
	
	ramNodeIdentifier() : name(""), index(-1) {}
	ramNodeIdentifier(int index) : name(""), index(index) {}
	ramNodeIdentifier(const std::string &name) : name(name), index(-1) {}
	ramNodeIdentifier(const std::string &name, int index) : name(name), index(index) {}
	ramNodeIdentifier(const ramNodeIdentifier& copy) { *this = copy; }
	
	ramNodeIdentifier& operator=(const ramNodeIdentifier& copy)
	{
		name = copy.name;
		index = copy.index;
		return *this;
	}
	
	void set(const std::string &name, int index) { this->name = name; this->index = index; }
	void set(const std::string &name) { this->name = name; this->index = -1; }
	void set(int index) { this->name = ""; this->index = index; }
	
	void clear() { name = ""; index = -1; }
	
	bool isValid() const
	{
		if (name == "" && index == -1) return false;
		else return true;
	}
	
	friend std::ostream& operator<<(std::ostream &os, const ramNodeIdentifier& o)
	{
		if (o.isValid())
			os << "['" << o.name << "' : " << o.index << "]";
		else
			os << "(null)";
		return os;
	}
};