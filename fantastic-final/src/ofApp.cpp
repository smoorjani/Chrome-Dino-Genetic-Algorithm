#include "ofApp.h"

constexpr double TEXT_CENTER_SCALAR = 0.45;

void ofApp::draw_dino() {
	if (is_human_playing) {
		draw_player_dino();
		draw_best_ai_dino();
	}
	else {
		draw_ai_dino();
	}
	
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

void ofApp::draw_genetic_information() {
	string generation_message = "Generation: " + std::to_string(generation);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(generation_message, ofGetWindowWidth()/2 - 20, 20);

	std::vector<double> fittest_genes = individuals_.get_individuals()[individuals_.get_fittest()].get_genes();
	std::string fittest_genes_message = "Fittest Individual Genes: ";
	for (double gene : fittest_genes) {
		fittest_genes_message += std::to_string(gene) + " ";
	}
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(fittest_genes_message, ofGetWindowWidth() / 2 - 20, 40);
}

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

void ofApp::generation_reset() {
	obstacles_.clear();
	player_dino_.dino_.reset();

	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.reset();
		// TODO Test if cumulative fitness scores makes training better
		individuals_.individuals[individual_num].set_fitness_score(0);
	}

	score = 0;
	for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		// CHANGE CONSTANT TO WORK WITH SCREEN
		// TODO: replace 115 with difference in image heights
		obstacles_.push_back(obstacle(ofGetWindowWidth() + 50, DEFAULT_START_Y + 115));
	}
}

void ofApp::update_human_game() {
	if (!player_dino_.dino_.get_is_dead() && player_dino_.dino_.get_is_jumping() && player_dino_.dino_.get_dino_y() <= DEFAULT_START_Y) {
		player_dino_.dino_.update();
	}

	if (best_ai_.should_jump(obstacles_) && !best_ai_.dino_.get_is_jumping()) {
		best_ai_.dino_.jump();
	}

	if (best_ai_.dino_.get_is_jumping() && best_ai_.dino_.get_dino_y() <= DEFAULT_START_Y) {
		best_ai_.dino_.update();
	}

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

void ofApp::update_training() {
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
			}
			else if (dist_from_obst > 0 && dist_from_obst < 5 && !individuals_.individuals[individual_num].dino_.get_is_dead()) {
				individuals_.individuals[individual_num].increment_score(10);
			}
		}

		if (!individuals_.individuals[individual_num].dino_.get_is_dead()) {
			individuals_.individuals[individual_num].increment_score(POINTS_PER_FRAME * .1);
		}
	}
}

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
	std::string image_file_path = "big_chrome_dino.png";
	player_dino_.dino_.setup_image(image_file_path);
	jump_sound.load("beep.mp3");

	individuals_.initialize_population(5);
	for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
		individuals_.individuals[individual_num].dino_.setup_image(image_file_path);
	}

	std::string data_file = "data.csv";
	std::vector<double> best_genes = gene_data_writer::get_best_individual_genes(data_file);

	best_ai_.dino_.setup_image(image_file_path);
	//std::vector<double> best_genes = {-2, -1.9129, 8.84732, 2.28675};
	for (int gene_num = 0; gene_num < best_genes.size(); gene_num++) {
		best_ai_.set_gene(best_genes[gene_num], gene_num);
	}
	
	current_state_ = MENU;
	ofSetWindowTitle("Dino");

	srand(static_cast<unsigned>(time(0)));
	score = 0;
	generation = 0;

	obstacles_.push_back(obstacle(ofGetWindowWidth(), DEFAULT_START_Y + 110));
	for (int i = 1; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		obstacles_.push_back(obstacle(obstacles_[i-1].get_obstacle_x() + (rand() % SCREEN_OFFSET) + MIN_DIST_BETWEEN_OBSTACLES, DEFAULT_START_Y + 110));
	}
}

void ofApp::update(){
	if (current_state_ == RUNNING) {
		score += POINTS_PER_FRAME;

		for (int obstacle_num = 0; obstacle_num < obstacles_.size(); obstacle_num++) {
			int previous_index = (obstacle_num != 0 ? obstacle_num - 1 : MAX_NUMBER_OF_OBSTACLES - 1);
			obstacles_[obstacle_num].update(obstacles_[previous_index].get_obstacle_x());
		}

		if (is_human_playing) {
			update_human_game();
		}
		else {
			update_training();

			if (individuals_.are_all_dead()) {
				std::cout << "----------------------------------" << std::endl;
				std::cout << "Generation: " << generation << std::endl;

				for (int individual_num = 0; individual_num < individuals_.get_individuals().size(); individual_num++) {
					std::cout << "Individual " << individual_num << " ";
					std::cout << individuals_.get_individual(individual_num);

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