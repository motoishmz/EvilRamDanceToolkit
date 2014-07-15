#include "ofMain.h"
#include "ramMain.h"

#include "ramBaseScene.h"
#include "ramBaseFilter.h"

class MyFilter : public ramBaseFilter
{
	
public:
	string getName() const { return "myfilter"; }
	
	void setupControlPanel()
	{
		ramGetGUI().getCurrentUIContext()->addSlider("test", 0.0, 1.0, 0.5);
	}
	const ramNodeArray& filter(const ramNodeArray& src)
	{
		return src;
	}
	
};

class MyScene : public ramBaseScene
{
	MyFilter f;
public:
	
	string getName() const { return "my name" + ofToString(ofRandomf()); }
	
	void setupControlPanel()
	{
		f.setupControlPanel();
		ramGetGUI().getCurrentUIContext()->addFPS();
	}
};

MyScene scene, scene2;
MyFilter filter;

class ofApp : public ofBaseApp
{
	
public:
	
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		
		ramGetGUI().setup();
		ramGetSceneManager().addScene(&scene);
		ramGetSceneManager().addScene(&scene2);
		
		ramGetGUI().addPanel(&filter);
	}
	
	void update()
	{
	}
	
	void draw()
	{
		
	}
	
	void keyPressed(int key)
	{
		
	}
	void mouseMoved(int x, int y)
	{
		
	}
	void mouseDragged( int x, int y, int button)
	{
		
	}
	void mousePressed( int x, int y, int button)
	{
		
	}
	void mouseReleased(int x, int y, int button)
	{
		
	}
	void dragEvent(ofDragInfo & drag)
	{
		const string file = drag.files[0];
	}
	
	void guiEvent(ofxUIEventArgs &e)
	{
		
	}
};



#pragma mark -
#pragma mark main
int main(){
	ofSetupOpenGL(1600, 900, OF_WINDOW);
	ofRunApp(new ofApp());
}
