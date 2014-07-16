#pragma once
#include "ofVec3f.h"
#include "ofUtils.h"
#include "ofxOscMessage.h"
#include "ramNode.h"

//
//// !!!:
//enum ramNodeArrayType
//{
//	RAM_NODEARRAY_TYPE_ACTOR     = 0,
//	RAM_NODEARRAY_TYPE_RIGIDBODY = 1
//};


class ramNodeArray
{
	
protected:
	// !!!:
	enum ramNodeArrayType
	{
		RAM_NODEARRAY_TYPE_ACTOR     = 0,
		RAM_NODEARRAY_TYPE_RIGIDBODY = 1
	};
	
public:
	
	//! constructors
	ramNodeArray();
	ramNodeArray(const string &name);
	ramNodeArray(const ramNodeArray& copy);
	virtual ~ramNodeArray();
	
	//! timestamps
	bool isOutdated() const;
	float getTimestamp() const;
	void setTimestamp(const float t);
	
	//! type
	void setType(ramNodeArrayType type);
	bool isActor() const;
	bool isRigid() const;
	bool isTypeOf(ramNodeArrayType type) const;
    
	//! playback
	void setPlayback(bool b);
	bool isPlayback() const;
    
	//! this method which is called by oscreceiver in ramActorManager drives ramdancetoolkit...
	virtual void updateWithOscMessage(const ofxOscMessage &m);
    
	//! utils
    ofVec3f getCentroid() const;
	string getJointName(unsigned int index) const;
	
	//! operators
		
	
	ramNodeArray& operator=(const ramNodeArray& copy);
	
	void setName(const string& name) { this->name = name; }
	const string& getName() const { return name; }
	
	size_t getNumNode() const { return nodes.size(); }
	
	ramNode& getNode(int node_id) { return nodes[node_id]; }
	const ramNode& getNode(int node_id) const { return nodes[node_id]; }
	
	
	
	// operators
	bool operator==(const ramNodeArray &arr) const;
	bool operator!=(const ramNodeArray &arr) const;
	
	ramNodeArray operator+(const ramNodeArray &arr) const;
	ramNodeArray& operator+=(const ramNodeArray &arr);
	
	ramNodeArray operator-(const ramNodeArray &arr) const;
	ramNodeArray& operator-=(const ramNodeArray &arr);
	
	ramNodeArray& lerp(const ramNodeArray &base, float t);
	ramNodeArray getLerpd(const ramNodeArray &base, float t) const;
	
	ramNodeArray& normalize(const ramNodeArray &base, float length);
	ramNodeArray getNormalized(const ramNodeArray &base, float length) const;
	
	ramNodeArray& limit(const ramNodeArray &base, float length);
	ramNodeArray getLimited(const ramNodeArray &base, float length) const;
    
protected:
	
	string name;
	vector<ramNode> nodes;
	
	void rebuildHierarchy(const ramNodeArray& ref);
	void clearHierarchy();
	void rebuildLocalPosition();
	
	
	ramNodeArrayType type;
    bool is_playback;
	
	float last_timestamp;
	float current_timestamp;
	float last_update_client_time;
};