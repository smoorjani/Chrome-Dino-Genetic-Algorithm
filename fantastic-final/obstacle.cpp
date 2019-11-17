#include "obstacle.h"

obstacle::obstacle(int x, int y) {
	obstacle_x = x;
	obstacle_y = y;
	obstacle_width = DEFAULT_OBSTACLE_WIDTH;
	obstacle_height = DEFAULT_OBSTACLE_HEIGHT;
}

obstacle::obstacle(int x, int y, int width, int height) {
    obstacle_x = x;
    obstacle_y = y;
    obstacle_width = width;
    obstacle_height = height;
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