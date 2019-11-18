#pragma once

#include "ofMain.h"
#include "dino.h"
#include <vector>

enum GameState { RUNNING = 0, PAUSED, FINISHED };

class ofApp : public ofBaseApp{
	private:
		GameState current_state_ = RUNNING;
		dino dino_;
		std::vector<obstacle> obstacles_;
		bool should_update_ = true;

		void draw_dino();
		void draw_obstacles();
		void reset();

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
};
