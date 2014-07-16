#pragma once
#include "ramActorManager.h"
#include "ramNodeIdentifier.h"
#include "ramInteractivePrimitive.h"
#include "ramGraphics.h"

using namespace ramInteractivePrimitives;

class ramActorManager::NodeSelector : public ramInteractivePrimitives::Node
{
public:
	
	enum
	{
		NODE_SELECTOR_PREFIX_ID = 1000
	};
	
	ofEvent<ramNodeIdentifier> selectStateChanged;
	ramNodeIdentifier identifer;
	
	NodeSelector(RootNode &root) { setParent(&root); }
	
	void draw()
	{
		ramActorManager &AM = ramActorManager::instance();
		const vector<GLuint> &NS = getCurrentNameStack();
		
		ofNoFill();
		
		for (int n = 0; n < AM.getNumNodeArray(); n++)
		{
			ramNodeArray &NA = AM.getNodeArray(n);
			
			for (int i = 0; i < NA.getNumNode(); i++)
			{
				ramNode &node = NA.getNode(i);
				
				glPushMatrix();
				ofTranslate(node.getGlobalPosition());
				ramBillboard();
				
				if (NS.size() == 3
					&& NS[1] == n
					&& NS[2] == i)
				{
					ofSetColor(255, 0, 0);
					ofCircle(0, 0, 10 + sin(ofGetElapsedTimef() * 20) * 5);
				}
				
				glPopMatrix();
			}
		}
	}
	
	void hittest()
	{
		ofFill();
		
		pushID(NODE_SELECTOR_PREFIX_ID);
		
		ramActorManager &AM = ramActorManager::instance();
		for (int n = 0; n < AM.getNumNodeArray(); n++)
		{
			ramNodeArray &NA = AM.getNodeArray(n);
			
			pushID(n);
			
			for (int i = 0; i < NA.getNumNode(); i++)
			{
				ramNode &node = NA.getNode(i);
				
				pushID(i);
				
				glPushMatrix();
				ofTranslate(node.getGlobalPosition());
				ramBillboard();
				
				ofCircle(0, 0, 15);
				
				glPopMatrix();
				
				popID();
			}
			
			popID();
		}
		
		popID();
	}
	
	void mousePressed(int x, int y, int button)
	{
		const vector<GLuint> &NS = getCurrentNameStack();
		ramActorManager &AM = ramActorManager::instance();
		
		if (NS.size() == 3 && NS[0] == NODE_SELECTOR_PREFIX_ID)
		{
			const ramNodeArray &NA = AM.getNodeArray(NS[1]);
			string name = NA.getName();
			int index = NS[2];
			
			identifer.name = name;
			identifer.index = index;
			
			ofNotifyEvent(selectStateChanged, identifer);
			
			//!!!:
//			ramEnableInteractiveCamera(false);
		}
		else
		{
			identifer.name = "";
			identifer.index = -1;
			
			ofNotifyEvent(selectStateChanged, identifer);
		}
	}
	
	void mouseReleased(int x, int y, int button)
	{
		//!!!:
//		ramEnableInteractiveCamera(true);
	}
	
	bool isObjectPickedUp()
	{
		return !getCurrentNameStack().empty();
	}
};