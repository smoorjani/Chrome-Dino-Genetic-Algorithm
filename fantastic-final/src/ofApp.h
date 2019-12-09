#pragma once

#include "ofMain.h"
#include "game/dino.h"
#include "game/obstacle.h"
#include "genetics/population.h"
#include "output/gene_data_writer.h"
#include <vector>

enum GameState { RUNNING = 0, PAUSED, FINISHED, MENU };
constexpr float POINTS_PER_FRAME = 0.25;

class ofApp : public ofBaseApp{
	private:
		ofSoundPlayer jump_sound;

		GameState current_state_ = RUNNING;
		// TODO Change variable name to player_individual
		individual player_dino_;
		individual best_ai_;

		population individuals_;
		std::vector<obstacle> obstacles_;
		bool should_update_ = true;
		bool is_human_playing = false;
		bool draw_hitboxes = false;

		float score;
		// TODO Display this on screen
		int generation;

		void draw_dino();
		void draw_player_dino();
		void draw_ai_dino();
		void draw_best_ai_dino();

		void draw_obstacles();
		void draw_score();
		void draw_game_over();
		void draw_menu();
		void draw_game_paused();

		void reset();
		void generation_reset();

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
};
