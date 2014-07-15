#include "ofMain.h"
#include "ramMain.h"


class MyScene : public ramBaseScene
{
public:
	
	string getName() const { return "my name"; }
	
	void setupControlPanel()
	{
		ramGetGUI().getCurrentUIContext()->addFPS();
	}
};


MyScene scene;

class ofApp : public ofBaseApp
{
	
public:
	
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		
		
		ramGetGUI().setup();
		ramGetSceneManager().addScene(&scene);
		
		
		
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
