#include "ofApp.h"

// TODO break this function up
void ofApp::draw_dino() {
	// Visualize player dino
	if (is_human_playing) {
		draw_player_dino();
	}
	draw_ai_dino();
}

void ofApp::draw_player_dino() {
	player_dino_.dino_.get_dino_image().draw(player_dino_.dino_.get_dino_x(), player_dino_.dino_.get_dino_y());

	// Visualize Dino Hitbox
	if (draw_hitboxes) {
		ofSetColor(player_dino_.dino_.get_dino_color());
		ofDrawRectangle(player_dino_.dino_.get_dino_hitbox());
	}
}

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
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(lose_message, ofGetWindowWidth() / 2,
		ofGetWindowHeight() / 2);
}

void ofApp::draw_menu() {
	string menu_header = "Chrome Dino GA";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(menu_header, ofGetWindowWidth() / 2,
		ofGetWindowHeight() / 3);

	string options = "(1) Train Dino \n(2) Play Dino \n(ESC) Exit";
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(options, ofGetWindowWidth() / 2,
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
	player_dino_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
	}

	setup();
}

void ofApp::generation_reset() {
	obstacles_.clear();
	player_dino_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
		
		// TODO Test if cumulative fitness scores makes training better
		individuals_.individuals[individual_num].set_fitness_score(0);

		// TODO would making jumps less desireable make the AI more effective?
	}

	score = 0;
	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		// TODO: replace 115 with difference in image heights
		obstacles_.push_back(obstacle(ofGetWindowWidth() + 50, DEFAULT_START_Y + 115));
	}
}

void ofApp::setup(){
	std::string file_path = "big_chrome_dino.png";
	player_dino_.dino_.setup_image(file_path);
	jump_sound.load("beep.mp3");

	individuals_.initialize_population(5);
	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.setup_image(file_path);
	}

	// ----------------------------------------
	// BEST AI so far - Demonstration purposes
	std::vector<double> best_genes = {-2, -1.9129, 8.84732, 2.28675};
	for (int gene_num = 0; gene_num < best_genes.size(); gene_num++) {
		individuals_.individuals[0].set_gene(best_genes[gene_num], gene_num);
	}
	// ----------------------------------------
	
	current_state_ = MENU;
	ofSetWindowTitle("Dino");

	srand(static_cast<unsigned>(time(0)));
	score = 0;
	generation = 0;

	obstacles_.push_back(obstacle(ofGetWindowWidth(), DEFAULT_START_Y + 110));
	for (int i = 1; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		// SCREEN_OFFSET or 400?
		obstacles_.push_back(obstacle(obstacles_[i-1].get_obstacle_x() + (rand() % SCREEN_OFFSET) + MIN_DIST_BETWEEN_OBSTACLES, DEFAULT_START_Y + 110));
	}
}

// breakup this function
void ofApp::update(){
	if (current_state_ == RUNNING) {
		score += POINTS_PER_FRAME;

		if (is_human_playing) {
			if (!player_dino_.dino_.get_is_dead() && player_dino_.dino_.get_is_jumping() && player_dino_.dino_.get_dino_y() <= DEFAULT_START_Y) {
				player_dino_.dino_.update();
			}

			for (auto& obstacle : obstacles_) {
				if (player_dino_.dino_.has_collided(obstacle)) {
					player_dino_.dino_.set_is_dead(true);

					if (is_human_playing) {
						current_state_ = FINISHED;
					}
				}
			}
		}

		for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
			individual temp_individual = individuals_.individuals[individual_num];
			if (temp_individual.dino_.get_is_dead()) {
				continue;
			}

			if (temp_individual.should_jump(obstacles_) && !temp_individual.dino_.get_is_jumping()) {
				individuals_.individuals[individual_num].dino_.jump();

				// deincentivize jumping
				individuals_.individuals[individual_num].decrease_score(JUMP_PENALTY);
			}

			if (temp_individual.dino_.get_is_jumping() && temp_individual.dino_.get_dino_y() <= DEFAULT_START_Y) {
				individuals_.individuals[individual_num].dino_.update();
			}

			for (auto& obstacle : obstacles_) {
				float dist_from_obst = individuals_.individuals[individual_num].dino_.get_dino_hitbox().getX() - obstacle.get_obstacle_hitbox().getX() + obstacle.get_obstacle_hitbox().getWidth();
				if (individuals_.individuals[individual_num].dino_.has_collided(obstacle)) {
					individuals_.individuals[individual_num].dino_.set_is_dead(true);
					// TODO make characteristic to stop player when collides
				}
				else if (dist_from_obst > 0 && dist_from_obst < 5 && !individuals_.individuals[individual_num].dino_.get_is_dead()) {
					individuals_.individuals[individual_num].increment_score(10);
				}
			}
			
			// Add points if the dino jumps over an obstacle successfully

			// if dino hitbox is to right of obstacle hitbox by 1 px and not dead



			if (!individuals_.individuals[individual_num].dino_.get_is_dead()) {
				individuals_.individuals[individual_num].increment_score(POINTS_PER_FRAME * .1);
			}
		}

		for (int obstacle_num = 0; obstacle_num < obstacles_.size(); obstacle_num++) {
			int previous_index = (obstacle_num != 0 ? obstacle_num - 1 : MAX_NUMBER_OF_OBSTACLES - 1);
			obstacles_[obstacle_num].update(obstacles_[previous_index].get_obstacle_x());
		}

		if (individuals_.are_all_dead() && !is_human_playing) {
			std::cout << "----------------------------------" << std::endl;
			std::cout << "Generation: " << generation << std::endl;

			for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
				std::cout << "Individual " << individual_num << " Fitness Score: " << individuals_.get_individual(individual_num).get_fitness_score() << " Genes: ";
				
				std::vector<double> genes = individuals_.get_individual(individual_num).get_genes();
				for (double gene : genes) {
					std::cout << gene << " ";
				}
				std::cout << std::endl;

				gene_data_writer::save_data_to_csv(generation, individual_num, individuals_.get_individual(individual_num).get_fitness_score(), genes);
			}
			
			
			generation_reset();

			individuals_.selection();
			individuals_.crossover();

			// CHANGE CONSTANTS HERE
			if (rand() % 7 < 4) {
				individuals_.mutation();
			}

			individuals_.add_fittest_offspring();

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
	else if (current_state_ == MENU) {
		draw_menu();
		return;
	}
	draw_dino();
	draw_obstacles();
	draw_score();
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
        reset();
		current_state_ = RUNNING;
		return;
	}
	else if (key == 'm') {
		reset();
	}
}