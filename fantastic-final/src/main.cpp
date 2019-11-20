#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	std::cout << "started" << std::endl;
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	ofSetFrameRate(60);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
