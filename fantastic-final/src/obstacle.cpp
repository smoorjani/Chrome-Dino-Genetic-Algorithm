#include "obstacle.h"

const float obstacle::obstacle_proportion_scalar = 0.1;

obstacle::obstacle(int x, int y) {
	obstacle_x = x;
	obstacle_y = y;

	int window_width = ofGetWindowWidth();
	int window_height = ofGetWindowHeight();
	window_dims.set(window_width, window_height);

	obstacle_width = obstacle_proportion_scalar * window_width;
	obstacle_height = obstacle_proportion_scalar * window_height;
	obstacle_hitbox.setSize(obstacle_width, obstacle_height);
	obstacle_hitbox.setPosition(obstacle_x, obstacle_y);
	
	obstacle_color.set(255,0,0);
}

obstacle::obstacle(int x, int y, int width, int height) {
    obstacle_x = x;
    obstacle_y = y;

    obstacle_width = width;
    obstacle_height = height;
	obstacle_hitbox.setSize(obstacle_width, obstacle_height);
	obstacle_hitbox.setPosition(obstacle_x, obstacle_y);

	obstacle_color.set(255, 0, 0);
}

int obstacle::get_obstacle_x() const {
	return obstacle_x;
}

int obstacle::get_obstacle_y() const {
	return obstacle_y;
}

int obstacle::get_obstacle_width() const {
	return obstacle_width;
}

int obstacle::get_obstacle_height() const {
	return obstacle_height;
}