#include "ramNodeArray.h"
#include "ramConstants.h"



#pragma mark -
#pragma mark constructors
ramNodeArray::ramNodeArray()
{}

ramNodeArray::ramNodeArray(const string &name)
: name(name)
{}

ramNodeArray::ramNodeArray(const ramNodeArray& copy)
{ *this = copy; }

ramNodeArray& ramNodeArray::operator=(const ramNodeArray& copy)
{}

ramNodeArray::~ramNodeArray()
{}



#pragma mark -
#pragma mark accessors

/*!
 timestamps
 */
inline bool ramNodeArray::isOutdated() const
{
	return (ofGetElapsedTimef() - last_update_client_time) > RAM_OUTDATED_DURATION;
}
inline float ramNodeArray::getTimestamp() const
{
	return last_update_client_time;
}
inline void ramNodeArray::setTimestamp(const float t)
{
	last_update_client_time = t;
}

/*!
 type
 */
inline void ramNodeArray::setType(ramNodeArrayType type)
{
	this->type = type;
}
inline bool ramNodeArray::isActor() const
{
	return type == RAM_NODEARRAY_TYPE_ACTOR;
}
inline bool ramNodeArray::isRigid() const
{
	return type == RAM_NODEARRAY_TYPE_RIGIDBODY;
}
inline bool ramNodeArray::isTypeOf(ramNodeArrayType type) const
{
	return this->type == type;
}

/*!
 is_playback
 */
inline void ramNodeArray::setPlayback(bool b)
{
	is_playback = b;
}
inline bool ramNodeArray::isPlayback() const
{
	return is_playback;
}

void ramNodeArray::updateWithOscMessage(const ofxOscMessage &m)
{
	const int nNodes = m.getArgAsInt32(1);
	
	for (int i = 0; i < nNodes; i++)
	{
		const string name = m.getArgAsString(i * 8 + 0 + 2);
		const float vx = m.getArgAsFloat(i * 8 + 1 + 2);
		const float vy = m.getArgAsFloat(i * 8 + 2 + 2);
		const float vz = m.getArgAsFloat(i * 8 + 3 + 2);
		const float angle = m.getArgAsFloat(i * 8 + 4 + 2);
		const float ax = m.getArgAsFloat(i * 8 + 5 + 2);
		const float ay = m.getArgAsFloat(i * 8 + 6 + 2);
		const float az = m.getArgAsFloat(i * 8 + 7 + 2);
		const ofVec3f axis(ax, ay, az);
		const ofVec3f vec(vx, vy, vz);
		const ofQuaternion quat(angle, axis);
		
		ramNode &node = getNode(i);
		node.node_id = i;
		node.node_name = getJointName(i);
		node.update(vec, quat);
	}
	
	last_timestamp = current_timestamp;
	current_timestamp = m.getArgAsFloat(2 + nNodes * 8);
	last_update_client_time = ofGetElapsedTimef();
}

#pragma mark -
#pragma mark utils
ofVec3f ramNodeArray::getCentroid() const
{
    ofVec3f centroid(0,0,0);
    
    for (int i = 0; i < getNumNode(); i++)
    {
        const ramNode &node = getNode(i);
        centroid += node.getGlobalPosition();
    }
    
    centroid /= getNumNode();
    
    return centroid;
}

string ramNodeArray::getJointName(unsigned int index) const
{
	return isActor() ? jointName[index] : "Node " + ofToString(index);
}


