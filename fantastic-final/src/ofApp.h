#pragma once

#include "ofMain.h"
#include "game/dino.h"
#include "game/obstacle.h"
#include "genetics/population.h"
#include "output/gene_data_writer.h"

#include "../addons/ofxGraph/src/ofxGraph.h"

#include <vector>

enum GameState { RUNNING = 0, PAUSED, FINISHED, MENU };
constexpr float POINTS_PER_FRAME = 0.25;

class ofApp : public ofBaseApp{
	private:
		ofxGraph graph;
		ofSoundPlayer jump_sound;

		GameState current_state_ = RUNNING;
		individual player_dino_;
		individual best_ai_;

		population individuals_;
		std::vector<obstacle> obstacles_;

		bool should_update_ = true;
		bool is_human_playing = false;
		bool human_won = false;
		bool draw_hitboxes = false;

		float score;
		int generation;

		// Functions to draw game objects/states
		void draw_dino();
		void draw_player_dino();
		void draw_ai_dino();
		void draw_best_ai_dino();

		void draw_obstacles();
		void draw_score();
		void draw_genetic_information();
		void draw_game_over();
		void draw_menu();
		void draw_game_paused();

		// Resets entire game instance
		void reset();
		// Prepares for next generation training cycle
		void generation_reset();

		// Update functionality for when human is playing
		void update_human_game();
		// Update functionality for when AI is being trained
		void update_training();
		// Wrapper code to contain all changes made to genetics by genetic algorithm
		void generation_transition();

	public:
		void setup();
		void setup_graph();

		void update();
		void draw();

		void keyPressed(int key);
};
