#pragma once
#include "ofNode.h"
#include "ramAccelerometer.h"

class ramNode : public ofNode
{
	// !!!
	// friend classから直で色々update。あんまりsetterをつくりたくない
	friend class ramNodeArray;
	friend class ramActor;
	friend class ramRigidBody;
	
public:
	
	ramNode();
	ramNode(int index);
	
	ramNode(const ramNode& copy);
	ramNode& operator=(const ramNode& copy);
	
	void update(const ofVec3f& vec, const ofQuaternion& quat);
	
	//! draw
	void drawNodeId(int floatPos = 20) const;
	void drawNodeName(int floatPos = 20) const;
	
	//! accessors ramNode
	const int getID() const;
	const string& getName() const;
	
	//! accessors: ofNode
	const ofMatrix4x4& getTransformMatrix() const;
	const ofMatrix4x4& getMatrix() const;
	bool hasParent() const;
	ramNode* getParent() const;
	void setParent(ramNode &parent);
	
	//! accessors: accelerometer
	ofVec3f getVelocity() const;
	ofVec3f getAcceleration() const;
	ofQuaternion getAngularVelocity() const;
	ofQuaternion getAngularAcceleration() const;
	ramAccelerometer& getAccelerometer();
	
	// operators
	operator ofVec3f() const;
	
	bool operator==(const ramNode &node) const;
	bool operator!=(const ramNode &node) const;
	
	ramNode operator+(const ramNode &node) const;
	ramNode& operator+=(const ramNode &node);
	
	ramNode operator-(const ramNode &node) const;
	ramNode& operator-=(const ramNode &node);
	
	ramNode& lerp(const ramNode &base, float t);
	ramNode getLerpd(const ramNode &base, float t) const;
	
	ramNode& normalize(const ramNode &base, float length);
	ramNode getNormalized(const ramNode &base, float length) const;
	
	ramNode& limit(const ramNode &base, float length);
	ramNode getLimited(const ramNode &base, float length) const;
	
	// utils
	void beginTransform() const;
	void endTransform() const;
	
protected:
	
	int node_id;
	string node_name;
	
	ramAccelerometer accelerometer;
};