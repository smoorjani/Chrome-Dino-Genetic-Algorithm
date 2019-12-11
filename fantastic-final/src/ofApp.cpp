#include "ofApp.h"

constexpr double TEXT_CENTER_SCALAR = 0.45;

// Wrapper function to handle logic behind which dinos to draw
void ofApp::draw_dino() {
	if (is_human_playing) {
		draw_player_dino();
		draw_best_ai_dino();
	}
	else {
		draw_ai_dino();
	}
	
}

// Draw the player-controlled dino
void ofApp::draw_player_dino() {
	player_dino_.dino_.get_dino_image().draw(player_dino_.dino_.get_dino_x(), player_dino_.dino_.get_dino_y());

	// Visualize Dino Hitbox
	if (draw_hitboxes) {
		ofSetColor(player_dino_.dino_.get_dino_color());
		ofDrawRectangle(player_dino_.dino_.get_dino_hitbox());
	}
}

// Draws all dinos in population that are being trained
void ofApp::draw_ai_dino() {
	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		dino temp_dino = individuals_.individuals[individual_num].dino_;
		if (temp_dino.get_is_dead()) {
			continue;
		}

		temp_dino.get_dino_image().draw(temp_dino.get_dino_x(), temp_dino.get_dino_y());

		// Visualize Obstacle Hitbox
		if (draw_hitboxes) {
			ofSetColor(temp_dino.get_dino_color());
			ofDrawRectangle(temp_dino.get_dino_hitbox());
		}
	}
}

// Draw the pre-loaded AI dino (loaded from CSV file)
void ofApp::draw_best_ai_dino() {
	best_ai_.dino_.get_dino_image().draw(best_ai_.dino_.get_dino_x(), best_ai_.dino_.get_dino_y());

	// Visualize Dino Hitbox
	if (draw_hitboxes) {
		ofSetColor(best_ai_.dino_.get_dino_color());
		ofDrawRectangle(best_ai_.dino_.get_dino_hitbox());
	}
}

void ofApp::draw_obstacles() {
	for (auto& obstacle : obstacles_) {	
		obstacle.get_obstacle_image().draw(obstacle.get_obstacle_x(), obstacle.get_obstacle_y());

		// Visualize Obstacle Hitbox
		if (draw_hitboxes) {
			ofSetColor(obstacle.get_obstacle_color());
			ofDrawRectangle(obstacle.get_obstacle_hitbox());
		}
	}
}

void ofApp::draw_game_over() {
	string lose_message = "You Lost! Final Score: " + std::to_string(int(score));
	string win_message = "You Won! Final Score: " + std::to_string(int(score));

	ofSetColor(0, 0, 0);
	if (!human_won) {
		ofDrawBitmapString(lose_message, ofGetWindowWidth() / 2,
			ofGetWindowHeight() / 2);
	}
	else {
		ofDrawBitmapString(win_message, ofGetWindowWidth() / 2,
			ofGetWindowHeight() / 2);
	}
	
}

void ofApp::draw_menu() {
	string menu_header = "Chrome Dino GA";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(menu_header, ofGetWindowWidth() * TEXT_CENTER_SCALAR,
		ofGetWindowHeight() / 3);

	string options = "(1) Train Dino \n(2) Play Dino \n(ESC) Exit";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(options, ofGetWindowWidth() * TEXT_CENTER_SCALAR,
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

// Draws generation info along with the genes of the fittest individual
void ofApp::draw_genetic_information() {
	string generation_message = "Generation: " + std::to_string(generation);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(generation_message, ofGetWindowWidth()/2 - 20, 20);

	std::vector<double> fittest_genes = individuals_.get_individuals()[individuals_.get_fittest()].get_genes();
	std::string fittest_genes_message = "Fittest Genes: ";
	for (double gene : fittest_genes) {
		fittest_genes_message += std::to_string(gene) + " ";
	}
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(fittest_genes_message, ofGetWindowWidth() / 2 - 20, 40);

	std::vector<double> second_fittest_genes = individuals_.get_individuals()[individuals_.get_second_fittest()].get_genes();
	std::string second_fittest_genes_message = "Second Fittest Genes: ";
	for (double gene : second_fittest_genes) {
		second_fittest_genes_message += std::to_string(gene) + " ";
	}
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(second_fittest_genes_message, ofGetWindowWidth() / 2 - 20, 60);
}

// Resets entire game instance and calls setup
void ofApp::reset() {
	obstacles_.clear();
	individuals_.clear();
	player_dino_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
	}

	is_human_playing = false;
	human_won = false;
	setup();
}

// Resets basic game features and all necessary genetic information
void ofApp::generation_reset() {
	obstacles_.clear();
	//player_dino_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
		individuals_.individuals[individual_num].set_fitness_score(0);
	}

	score = 0;
	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		// TODO: replace 115 with difference in image heights
		obstacles_.push_back(obstacle(ofGetWindowWidth() + 50, DEFAULT_START_Y + 115));
	}
}

// If the human is playing, only update relevant objects (player dino, pre-loaded ai)
void ofApp::update_human_game() {
	// If the player's dino is jumping and isn't dead, continue updating it's position
	// Prevents dino from going below DEFAULT_START_Y
	if (!player_dino_.dino_.get_is_dead() && player_dino_.dino_.get_is_jumping() && player_dino_.dino_.get_dino_y() <= DEFAULT_START_Y) {
		player_dino_.dino_.update();
	}

	if (best_ai_.should_jump(obstacles_) && !best_ai_.dino_.get_is_jumping()) {
		best_ai_.dino_.jump();
	}

	// If the pre-loaded AI's dino is jumping and isn't dead, continue updating it's position
	// Prevents dino from going below DEFAULT_START_Y
	if (best_ai_.dino_.get_is_jumping() && best_ai_.dino_.get_dino_y() <= DEFAULT_START_Y) {
		best_ai_.dino_.update();
	}

	// Check for collisions with all obstacles
	for (auto& obstacle : obstacles_) {
		if (player_dino_.dino_.has_collided(obstacle)) {
			human_won = false;
			player_dino_.dino_.set_is_dead(true);
			current_state_ = FINISHED;
		}

		if (best_ai_.dino_.has_collided(obstacle)) {
			human_won = true;
			best_ai_.dino_.set_is_dead(true);
			current_state_ = FINISHED;
		}
	}
}

// If player is not playing, only update AI's being trained
void ofApp::update_training() {
	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individual temp_individual = individuals_.individuals[individual_num];
		// Skips all logic if the individual is dead
		if (temp_individual.dino_.get_is_dead()) {
			continue;
		}

		if (temp_individual.should_jump(obstacles_) && !temp_individual.dino_.get_is_jumping()) {
			individuals_.individuals[individual_num].dino_.jump();
			// deincentivize jumping with a jump penalty that affects fitness score
			individuals_.individuals[individual_num].decrease_score(JUMP_PENALTY);
		}

		// If the AI's dino is jumping and isn't dead, continue updating it's position
		if (temp_individual.dino_.get_is_jumping() && temp_individual.dino_.get_dino_y() <= DEFAULT_START_Y) {
			individuals_.individuals[individual_num].dino_.update();
		}

		for (auto& obstacle : obstacles_) {
			float dist_from_obst = individuals_.individuals[individual_num].dino_.get_dino_hitbox().getX() - obstacle.get_obstacle_hitbox().getX() + obstacle.get_obstacle_hitbox().getWidth();
			// Checks for collisions with all obstacles
			if (individuals_.individuals[individual_num].dino_.has_collided(obstacle)) {
				individuals_.individuals[individual_num].dino_.set_is_dead(true);
			}
			else if (dist_from_obst > 0 && dist_from_obst < 5 && !individuals_.individuals[individual_num].dino_.get_is_dead()) {
				// For every successful jump over a cactus, incremement the fitness score
				individuals_.individuals[individual_num].increment_score(10);
			}
		}
		// Basic reward for getting further on in the game
		if (!individuals_.individuals[individual_num].dino_.get_is_dead()) {
			individuals_.individuals[individual_num].increment_score(POINTS_PER_FRAME * .1);
		}
	}
}

// Main method to handle genetic algorithm
void ofApp::generation_transition() {
	generation_reset();

	individuals_.selection();
	individuals_.crossover();

	// CHANGE CONSTANTS HERE
	if (rand() % 7 < 4) {
		individuals_.mutation();
	}

	individuals_.add_fittest_offspring();
	generation++;
}

void ofApp::setup(){
	// Loads all necessary resources for the game
	jump_sound.load("beep.mp3");
	// Gets previous best AI based on fitness score for the pre-loaded AI
	// Previous best weights:
	// std::vector<double> best_genes = {-2, -1.9129, 8.84732, 2.28675};
	std::string data_file = "data.csv";
	std::vector<double> best_genes = gene_data_writer::get_best_individual_genes(data_file);

	for (int gene_num = 0; gene_num < best_genes.size(); gene_num++) {
		std::cout << best_genes[gene_num] << " ";
		best_ai_.set_gene(best_genes[gene_num], gene_num);
	}
	
	individuals_.initialize_population(5);

	current_state_ = MENU;
	ofSetWindowTitle("Dino");

	srand(static_cast<unsigned>(time(0)));
	score = 0;
	generation = 0;

	obstacles_.push_back(obstacle(ofGetWindowWidth(), DEFAULT_START_Y + 110));
	for (int i = 1; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		obstacles_.push_back(obstacle(obstacles_[i-1].get_obstacle_x() + (rand() % SCREEN_OFFSET) + MIN_DIST_BETWEEN_OBSTACLES, DEFAULT_START_Y + 110));
	}

	// Sets up ofxGraph for realtime graphing of data
	ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);
	graph.setup("Fitness score vs time");
	graph.setDx(5.0); // which means delta of time
	graph.setColor(ofColor::white);  // ofColor(255,255,255)
}

void ofApp::update(){
	if (current_state_ == RUNNING) {
		score += POINTS_PER_FRAME;

		// Updates the position of all obstacles
		for (int obstacle_num = 0; obstacle_num < obstacles_.size(); obstacle_num++) {
			int previous_index = (obstacle_num != 0 ? obstacle_num - 1 : MAX_NUMBER_OF_OBSTACLES - 1);
			obstacles_[obstacle_num].update(obstacles_[previous_index].get_obstacle_x());
		}

		if (is_human_playing) {
			update_human_game();
		}
		else {
			update_training();
			individual fittest_individual = individuals_.get_individual(individuals_.get_fittest());
			graph.add(fittest_individual.get_fitness_score());

			// Once all AIs are dead, reset the generation and apply genetic algorithm
			if (individuals_.are_all_dead()) {
				std::cout << "----------------------------------" << std::endl;
				std::cout << "Generation: " << generation << std::endl;

				for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
					std::cout << "Individual " << individual_num << " ";
					std::cout << individuals_.get_individual(individual_num);

					// Saves all outputted data to the csv file
					std::vector<double> genes = individuals_.get_individual(individual_num).get_genes();
					gene_data_writer::save_data_to_csv(generation, individual_num, individuals_.get_individual(individual_num).get_fitness_score(), genes);
				}

				generation_transition();
				return;
			}
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
	else if (current_state_ == MENU) {
		draw_menu();
		return;
	}
	draw_dino();
	draw_obstacles();
	draw_score();

	if (!is_human_playing) {
		graph.draw();
		draw_genetic_information();
	}
}

void ofApp::keyPressed(int key){ 
	if (is_human_playing && key == ' ') {
		if (!player_dino_.dino_.get_is_jumping()) {
			jump_sound.play();
			player_dino_.dino_.jump();
		}
		return;
	}

	int lower_key = tolower(key);
	
	if (key == '1' && current_state_ == MENU) {
		current_state_ = RUNNING;
	}
	else if (key == '2' && current_state_ == MENU) {
		is_human_playing = true;
		current_state_ = RUNNING;
	}

	if (key == 'p' && current_state_ != FINISHED) {
		if (current_state_ == PAUSED) {
			current_state_ = RUNNING;
		} else {
			current_state_ = PAUSED;
		}
		return;
    } else if (key == 'r' && (current_state_ == RUNNING || current_state_ == FINISHED)) {
		// bool to preserve distinct states after reset
		bool was_human_playing = is_human_playing;
        reset();
		is_human_playing = was_human_playing;
		current_state_ = RUNNING;
		return;
	}
	else if (key == 'm') {
		reset();
	}
}