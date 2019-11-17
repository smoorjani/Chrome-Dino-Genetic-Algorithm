#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() { 
	ofSetColor(0, 100, 0);
	ofDrawRectangle(0, 0, 100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
	if (key == OF_KEY_F12) {
        ofToggleFullscreen();
		return;
    } else if (key == ' ') {
        // JUMP

		return;
	}

	int upper_key = toupper(key);
	
	if (key == 'P') {
		// PAUSE
		return;
    } else if (key == 'R') {
        // RESET
		return;
	}
}