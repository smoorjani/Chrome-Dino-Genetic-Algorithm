#include "ofApp.h"

void ofApp::draw_dino() {
	dino_.get_dino_image().draw(dino_.get_dino_x(), dino_.get_dino_y());
}

void ofApp::draw_obstacles() {
	for (auto& obstacle : obstacles_) {
		ofSetColor(obstacle.get_obstacle_color());
		ofDrawRectangle(obstacle.get_obstacle_hitbox());
	}
}

void ofApp::draw_score() {
	string score_message = "Score: " + std::to_string(int(score));
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(score_message, 20, 20);
}

void ofApp::reset() {
	obstacles_.clear();
	setup();
}

//--------------------------------------------------------------
void ofApp::setup(){
	std::string file_path = "big_chrome_dino.png";;
	dino_.setup_image(file_path);

	current_state_ = RUNNING;
	ofSetWindowTitle("Dino");
	srand(static_cast<unsigned>(time(0)));
	score = 0;

	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		obstacles_.push_back(obstacle(ofGetWindowWidth(),DEFAULT_START_Y + 40));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if (current_state_ == RUNNING) {
		score += POINTS_PER_FRAME;
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
	draw_score();
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