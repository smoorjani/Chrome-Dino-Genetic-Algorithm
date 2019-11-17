#include "dino.h"

dino::dino() {
	dino_x = DEFAULT_START_X;
	dino_y = DEFAULT_START_Y;
	dino_height = DEFAULT_DINO_HEIGHT;
	dino_width = DEFAULT_DINO_WIDTH;
}

dino::dino(int x, int y, int width, int height) {
	dino_x = x;
	dino_y = y;
	dino_height = height;
	dino_width = width;
}

int dino::get_dino_x() const {
	return dino_x;
}

int dino::get_dino_y() const {
	return dino_y;
}

int dino::get_dino_width() const {
	return dino_width;
}

int dino::get_dino_height() const {
	return dino_height;
}

bool operator==(const dino& lhs, const obstacle& rhs) {
	if (lhs.get_dino_x() < rhs.get_obstacle_x() + rhs.get_obstacle_width() &&
		lhs.get_dino_x() + lhs.get_dino_width() > rhs.get_obstacle_x() &&
		lhs.get_dino_y() < rhs.get_obstacle_y() + rhs.get_obstacle_height() &&
		lhs.get_dino_y() + lhs.get_dino_height() > rhs.get_obstacle_y()) {
		return true;
	}
	return false;
}

bool operator!=(const dino& lhs, const obstacle& rhs) {
	return !(lhs == rhs);
}