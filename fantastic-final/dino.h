#pragma once
#include "obstacle.h"

constexpr int DEFAULT_DINO_WIDTH = 40;
constexpr int DEFAULT_DINO_HEIGHT = 40;
constexpr int DEFAULT_START_X = 40;
constexpr int DEFAULT_START_Y = 400;

class dino {
	private:
		int dino_x;
		int dino_y;
		int dino_width;
		int dino_height;

	public:
		dino();
		dino(int x, int y, int width, int height);

		int get_dino_x() const;
		int get_dino_y() const;
		int get_dino_width() const;
		int get_dino_height() const;

		friend bool operator==(dino &lhs, obstacle &rhs);
		friend bool operator!=(dino& lhs, obstacle& rhs);
};
