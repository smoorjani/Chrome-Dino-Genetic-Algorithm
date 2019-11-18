#pragma once
#include "obstacle.h"

constexpr int DEFAULT_START_X = 40;
constexpr int DEFAULT_START_Y = 400;

class dino {
	private:
		int dino_x;
		int dino_y;
		int dino_width;
		int dino_height;

		bool is_jumping;

		ofVec2f window_dims;
		static const float dino_proportion_scalar;

		ofRectangle dino_hitbox;
		ofColor dino_color;

	public:
		dino();
		dino(int x, int y, int width, int height);

		int get_dino_x() const;
		int get_dino_y() const;
		int get_dino_width() const;
		int get_dino_height() const;

		bool is_jumping();
		void set_is_jumping(bool jumping);

		friend bool operator==(dino &lhs, obstacle &rhs);
		friend bool operator!=(dino& lhs, obstacle& rhs);

		ofRectangle get_dino_hitbox();
		ofColor get_dino_color();

		void jump();
};
