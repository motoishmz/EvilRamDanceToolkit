#pragma once
#include "ofxOsc.h"
#include "ramConstants.h"

struct ramOscSendTag{
	
	ramOscSendTag(int port_,string addr_){
		port = port_;
		address = addr_;
	}
	int port;
	string address;
	
};

class ramOscReceiveTag{
public:
	
	ramOscReceiveTag(string addr_){
		string ad = addr_;
		addr.push_back(ad);
	}
	ramOscReceiveTag(){
	}
	
	void addAddress(string addr_){
		string ad = addr_;
		addr.push_back(ad);
	}
	
	void addMessage(ofxOscMessage& m){
		msg.push_back(ofxOscMessage(m));
	}
	
	void getNextMessage(ofxOscMessage* m){
		(*m) = msg[0];
		msg.erase(msg.begin());
	}
	
	bool hasWaitingMessages(){return (msg.size() > 0);};
	
	vector<ofxOscMessage> msg;
	vector <string> addr;
	
};

class ramOscManager{
public:
	
	void setup(int receivePort);
	void update();
	
	void addSenderTag(int port,string address);
	void addReceiverTag(ramOscReceiveTag* ptr);
	
	inline static ramOscManager& instance()
	{
		if (__instance == NULL)
			__instance = new ramOscManager;
		return * __instance;
	}
	
	ofxOscReceiver* getReceiver()	{return &receiver;};
	ofxOscSender*	getSender()		{return &sender;};
	
private:
	static ramOscManager *__instance;
	
	ramOscManager() {};
	ramOscManager(const ramOscManager&){}
	ramOscManager& operator=(const ramOscManager&){return *this;}
	~ramOscManager() {};
	
	vector<ramOscReceiveTag*> receiverList;
	vector<ramOscSendTag> senderlist;
	
	ofxOscSender sender;
	ofxOscReceiver receiver;
	
};
