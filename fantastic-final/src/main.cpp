#include "ofMain.h"
#include "ofApp.h"
//#include "matplotlibcpp.h"

// Current best: -2 -1.9129 8.84732 2.28675

//========================================================================
int main() {
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	ofSetFrameRate(60);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
