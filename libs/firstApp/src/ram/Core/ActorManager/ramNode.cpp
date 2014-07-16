#include "ramNode.h"

ramNode::ramNode()
: ofNode()
, node_id(-1)
{}
ramNode::ramNode(int index)
: ofNode()
, node_id(index)
{}
ramNode::ramNode(const ramNode& copy)
{
	*this = copy;
}
ramNode& ramNode::operator=(const ramNode& copy)
{
	ofNode::operator=(copy);
	node_name = copy.node_name;
	node_id = copy.node_id;
	parent = copy.parent;
	accelerometer = copy.accelerometer;
	return *this;
}


#pragma mark -
#pragma mark draw
void ramNode::drawNodeId(int floatPos) const
{
	ofVec3f pos = getGlobalPosition();
	pos.y += floatPos;
	ofDrawBitmapString(ofToString(getID()), pos);
}
void ramNode::drawNodeName(int floatPos) const
{
	ofVec3f pos = getGlobalPosition();
	pos.y += floatPos;
	ofDrawBitmapString(ofToString(getName()), pos);
}


#pragma mark -
#pragma mark accessors: ramNode
//void ramNode::setName(const string name)
//{
//	//!!!:
//	cout << "本当は呼びたく無い" << endl;
//	node_name = name;
//}
const int ramNode::getID() const
{
	return node_id;
}
const string& ramNode::getName() const
{
	return node_name;
}


#pragma mark -
#pragma mark accessors: ofNode
const ofMatrix4x4& ramNode::getTransformMatrix() const
{
	return getLocalTransformMatrix();
}
const ofMatrix4x4& ramNode::getMatrix() const
{
	return getLocalTransformMatrix();
}
inline bool ramNode::hasParent() const
{
	return parent != NULL;
}
inline ramNode* ramNode::getParent() const
{
	return (ramNode*)parent;
}
inline void ramNode::setParent(ramNode &parent)
{
	this->parent = &parent;
}


#pragma mark -
#pragma mark accessors: ramAccelerometer
inline ofVec3f ramNode::getVelocity() const
{
	return accelerometer.velocity;
}
inline ofVec3f ramNode::getAcceleration() const
{
	return accelerometer.acceleration;
}
inline ofQuaternion ramNode::getAngularVelocity() const
{
	return accelerometer.angular_velocity;
}
inline ofQuaternion ramNode::getAngularAcceleration() const
{
	return accelerometer.angular_acceleration;
}
inline ramAccelerometer& ramNode::getAccelerometer()
{
	return accelerometer;
}


#pragma mark -
#pragma mark operators

inline ramNode::operator ofVec3f() const
{
	return getGlobalPosition();
}
inline bool ramNode::operator==(const ramNode &node) const
{
	const float *m = getLocalTransformMatrix().getPtr();
	const float *mm = node.getLocalTransformMatrix().getPtr();
	
	float r = 0;
	r += fabs(m[0] - mm[0]);
	r += fabs(m[1] - mm[1]);
	r += fabs(m[2] - mm[2]);
	
	r += fabs(m[4] - mm[4]);
	r += fabs(m[5] - mm[5]);
	r += fabs(m[6] - mm[6]);
	
	r += fabs(m[8] - mm[8]);
	r += fabs(m[9] - mm[9]);
	r += fabs(m[10] - mm[10]);
	
	if (r > 0.01)
	{
		return false;
	}
	
	float d = ofVec3f(m[12], m[13], m[14]).distance(ofVec3f(mm[12], mm[13], mm[14]));
	if (d > 0.2)
	{
		return false;
	}
	
	return true;
}
inline bool ramNode::operator!=(const ramNode &node) const
{
	return !(*this == node);
}
inline ramNode ramNode::operator+(const ramNode &node) const
{
	ramNode result = *this;
	
	result.setPosition(result.getPosition() + node.getPosition());
	result.setOrientation(result.getOrientationQuat() * node.getOrientationQuat());
	
	return result;
}
inline ramNode& ramNode::operator+=(const ramNode &node)
{
	ramNode &result = *this;
	
	result.setPosition(result.getPosition() + node.getPosition());
	result.setOrientation(result.getOrientationQuat() * node.getOrientationQuat());
	
	return result;
}
inline ramNode ramNode::operator-(const ramNode &node) const
{
	ramNode result = *this;
	
	result.setPosition(result.getPosition() - node.getPosition());
	result.setOrientation(result.getOrientationQuat() * node.getOrientationQuat().inverse());
	
	return result;
}
inline ramNode& ramNode::operator-=(const ramNode &node)
{
	ramNode &result = *this;
	
	result.setPosition(result.getPosition() - node.getPosition());
	result.setOrientation(result.getOrientationQuat() * node.getOrientationQuat().inverse());
	
	return result;
}
inline ramNode& ramNode::lerp(const ramNode &base, float t)
{
	const ofMatrix4x4& a = this->getGlobalTransformMatrix();
	const ofMatrix4x4& b = base.getGlobalTransformMatrix();
	
	ofQuaternion trot;
	trot.slerp(t, a.getRotate(), b.getRotate());
	setGlobalOrientation(trot);
	
	ofVec3f apos = a.getTranslation(), bpos = b.getTranslation();
	setGlobalPosition(apos.interpolate(bpos, t));
	
	return *this;
}
inline ramNode ramNode::getLerpd(const ramNode &base, float t) const
{
	ramNode result = *this;
	
	result.lerp(base, t);
	return result;
}
inline ramNode& ramNode::normalize(const ramNode &base, float length)
{
	ramNode &result = *this;
	
	const ofVec3f &p0 = result.getGlobalPosition();
	const ofVec3f &p1 = base.getGlobalPosition();
	
	ofVec3f d = (p0 - p1);
	d.normalize();
	d *= length;
	
	result.setGlobalPosition(p1 + d);
	
	return result;
}
inline ramNode ramNode::getNormalized(const ramNode &base, float length) const
{
	ramNode result = *this;
	
	const ofVec3f &p0 = result.getGlobalPosition();
	const ofVec3f &p1 = base.getGlobalPosition();
	
	ofVec3f d = (p0 - p1);
	d.normalize();
	d *= length;
	
	result.setGlobalPosition(p1 + d);
	
	return result;
}
inline ramNode& ramNode::limit(const ramNode &base, float length)
{
	ramNode &result = *this;
	
	const ofVec3f &p0 = result.getGlobalPosition();
	const ofVec3f &p1 = base.getGlobalPosition();
	
	ofVec3f d = (p0 - p1);
	d.limit(length);
	
	result.setGlobalPosition(p1 + d);
	
	return result;
}
inline ramNode ramNode::getLimited(const ramNode &base, float length) const
{
	ramNode result = *this;
	
	const ofVec3f &p0 = result.getGlobalPosition();
	const ofVec3f &p1 = base.getGlobalPosition();
	
	ofVec3f d = (p0 - p1);
	d.limit(length);
	
	result.setGlobalPosition(p1 + d);
	
	return result;
}




#pragma mark -
#pragma mark utils...
inline void ramNode::beginTransform() const
{
	transformGL();
}
inline void ramNode::endTransform() const
{
	restoreTransformGL();
}

