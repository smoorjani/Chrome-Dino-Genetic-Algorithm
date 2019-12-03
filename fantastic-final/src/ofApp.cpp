#include "ofApp.h"

void ofApp::draw_dino() {
	fittest_individual_.dino_.get_dino_image().draw(fittest_individual_.dino_.get_dino_x(), fittest_individual_.dino_.get_dino_y());
	
	// Visualize Dino Hitbox
	ofSetColor(fittest_individual_.dino_.get_dino_color());
	ofDrawRectangle(fittest_individual_.dino_.get_dino_hitbox());

	
	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		dino temp_dino = individuals_.individuals[individual_num].dino_;
		if (temp_dino.get_is_dead()) {
			continue;
		}

		temp_dino.get_dino_image().draw(temp_dino.get_dino_x(), temp_dino.get_dino_y());

		// Visualize Obstacle Hitbox
		ofSetColor(temp_dino.get_dino_color());
		ofDrawRectangle(temp_dino.get_dino_hitbox());
	}
}

void ofApp::draw_obstacles() {
	for (auto& obstacle : obstacles_) {	
		obstacle.get_obstacle_image().draw(obstacle.get_obstacle_x(), obstacle.get_obstacle_y());

		// Visualize Obstacle Hitbox
		ofSetColor(obstacle.get_obstacle_color());
		ofDrawRectangle(obstacle.get_obstacle_hitbox());
	}
}

void ofApp::draw_game_over() {
	string lose_message = "You Lost! Final Score: " + std::to_string(int(score));
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(lose_message, ofGetWindowWidth() / 2,
		ofGetWindowHeight() / 2);
}

void ofApp::draw_game_paused() {
	string pause_message = "P to Unpause!";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2,
		ofGetWindowHeight() / 2);
}


void ofApp::draw_score() {
	string score_message = "Score: " + std::to_string(int(score));
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(score_message, 20, 20);
}

void ofApp::reset() {
	obstacles_.clear();
	individuals_.clear();
	fittest_individual_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
	}

	setup();
}

void ofApp::generation_reset() {
	obstacles_.clear();
	fittest_individual_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
	}

	score = 0;
	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		obstacles_.push_back(obstacle(ofGetWindowWidth(), DEFAULT_START_Y + 115));
	}
}

void ofApp::setup(){
	std::string file_path = "big_chrome_dino.png";
	fittest_individual_.dino_.setup_image(file_path);

	individuals_.initialize_population(5);

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.setup_image(file_path);
	}

	current_state_ = RUNNING;
	ofSetWindowTitle("Dino");

	srand(static_cast<unsigned>(time(0)));
	score = 0;
	generation = 0;

	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		obstacles_.push_back(obstacle(ofGetWindowWidth(),DEFAULT_START_Y + 115));
	}
}

void ofApp::update(){
	if (current_state_ == RUNNING) {
		score += POINTS_PER_FRAME;

		for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
			individual temp_individual = individuals_.individuals[individual_num];
			if (temp_individual.dino_.get_is_dead()) {
				continue;
			}

			if (temp_individual.should_jump(obstacles_)) {
				individuals_.individuals[individual_num].dino_.jump();
			}

			if (temp_individual.dino_.get_is_jumping() && temp_individual.dino_.get_dino_y() <= DEFAULT_START_Y) {
				individuals_.individuals[individual_num].dino_.update();
			}

			for (auto& obstacle : obstacles_) {
				if (individuals_.individuals[individual_num].dino_.has_collided(obstacle)) {
					//std::cout << "dead bot" << std::endl;
					individuals_.individuals[individual_num].dino_.set_is_dead(true);
					// TODO make characteristic to stop player when collides
				}
			}
			
			individuals_.individuals[individual_num].increment_score(POINTS_PER_FRAME);
		}

		if (!fittest_individual_.dino_.get_is_dead() && fittest_individual_.dino_.get_is_jumping() && fittest_individual_.dino_.get_dino_y() <= DEFAULT_START_Y) {
			fittest_individual_.dino_.update();
		}
		for (auto& obstacle : obstacles_) {
			obstacle.update();

			if (fittest_individual_.dino_.has_collided(obstacle)) {
				//std::cout << "dead" << std::endl;
				fittest_individual_.dino_.set_is_dead(true);
				//current_state_ = FINISHED;
			}
		}

		if (individuals_.are_all_dead()) {
			generation_reset();

			individuals_.selection();
			individuals_.crossover();

			// CHANGE CONSTANTS HERE
			if (rand() % 7 < 4) {
				individuals_.mutation();
			}

			individuals_.add_fittest_offspring();

			std::cout << "----------------------------------" << std::endl;
			std::cout << "Generation: " << generation << std::endl;

			for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
				std::vector<double> genes = individuals_.get_individual(individual_num).get_genes();
				for (double gene : genes) {
					std::cout << gene << " ";
				}
				std::cout << std::endl;
			}
			
			generation++;

			return;
		}
	}
}

void ofApp::draw() { 
	if (current_state_ == FINISHED) {
		draw_game_over();
	}
	else if (current_state_ == PAUSED) {
		draw_game_paused();
	}
	draw_dino();
	draw_obstacles();
	draw_score();
}

void ofApp::keyPressed(int key){ 
	if (key == ' ') {
		if (!fittest_individual_.dino_.get_is_jumping()) {
			fittest_individual_.dino_.jump();
		}
		return;
	}

	int lower_key = tolower(key);
	
	if (key == 'p' && current_state_ != FINISHED) {
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