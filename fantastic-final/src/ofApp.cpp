#include "ofApp.h"

void ofApp::draw_dino() {
	ofSetColor(dino_.get_dino_color());
	ofDrawRectangle(dino_.get_dino_hitbox());
}

void ofApp::draw_obstacles() {

}

void ofApp::reset() {
	dino_ = dino();
	obstacles_.clear();
	current_state_ = RUNNING;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Dino");
	srand(static_cast<unsigned>(time(0)));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() { 
	draw_dino();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
	if (key == OF_KEY_F12) {
        ofToggleFullscreen();
		return;
    } else if (key == ' ') {
        // JUMP
		dino_.jump();
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