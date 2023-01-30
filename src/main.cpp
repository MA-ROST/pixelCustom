#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	const string title               = "Pixel Custom";
	constexpr Point <int> screenSize = {1000, 900};

	ofGLFWWindowSettings settings;
	settings.setSize(screenSize.x, screenSize.y);
	settings.title = title;
	settings.resizable = false;
	ofCreateWindow(settings);
	ofSetWindowTitle(title); // Set the window title


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
