#pragma once

#include "ofMain.h"
#include "dino.h"
#include "genetics/population.h"
#include <vector>

enum GameState { RUNNING = 0, PAUSED, FINISHED };
constexpr float POINTS_PER_FRAME = 0.25;

class ofApp : public ofBaseApp{
	private:
		GameState current_state_ = RUNNING;
		individual fittest_individual_;

		population individuals_;
		std::vector<obstacle> obstacles_;
		bool should_update_ = true;
		float score;

		void draw_dino();
		void draw_obstacles();
		void draw_score();
		void draw_game_over();
		void draw_game_paused();
		void reset();

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
};
