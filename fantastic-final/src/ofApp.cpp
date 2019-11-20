#include "ofApp.h"

void ofApp::draw_dino() {
	ofSetColor(dino_.get_dino_color());
	ofDrawRectangle(dino_.get_dino_hitbox());
}

void ofApp::draw_obstacles() {
	for (auto& obstacle : obstacles_) {
		ofSetColor(obstacle.get_obstacle_color());
		ofDrawRectangle(obstacle.get_obstacle_hitbox());
	}
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

	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		obstacles_.push_back(obstacle(ofGetWindowWidth(),DEFAULT_START_Y + 40));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if (current_state_ == RUNNING) {
		if (dino_.get_is_jumping() && dino_.get_dino_y() <= DEFAULT_START_Y) {
			dino_.update();
		}
		for (auto& obstacle : obstacles_) {
			obstacle.update();

			if (dino_ == obstacle) {
				std::cout << "dead" << std::endl;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() { 
	draw_dino();
	draw_obstacles();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){ 
	if (key == ' ') {
		if (!dino_.get_is_jumping()) {
			dino_.jump();
		}
		return;
	}

	int lower_key = tolower(key);
	
	if (key == 'p') {
		if (current_state_ == PAUSED) {
			current_state_ = RUNNING;
		} else {
			current_state_ = PAUSED;
		}
		return;
    } else if (key == 'r') {
        reset();
		return;
	}
}

/*
if (key == OF_KEY_F12) {
		ofToggleFullscreen();
		return;
	} else
*/