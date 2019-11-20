#pragma once
#include "obstacle.h"

constexpr float DEFAULT_START_X = 40;
constexpr float DEFAULT_START_Y = 400;
constexpr float GRAVITY = 0.5;
constexpr float JUMP_VELOCITY = 13;

class dino {
	private:
		float dino_x;
		float dino_y;
		float dino_velocity_y;
		float dino_width;
		float dino_height;

		bool is_jumping;

		ofVec2f window_dims;
		static const float dino_proportion_scalar;

		ofRectangle dino_hitbox;
		ofColor dino_color;

	public:
		dino();
		dino(float x, float y, float width, float height);

		float get_dino_x() const;
		float get_dino_y() const;
		float get_dino_width() const;
		float get_dino_height() const;

		float get_velocity_y() const;
		void set_velocity_y(float y_velocity);

		bool get_is_jumping() const;
		void set_is_jumping(bool jumping);

		friend bool operator==(dino &lhs, obstacle &rhs);
		friend bool operator!=(dino& lhs, obstacle& rhs);

		ofRectangle get_dino_hitbox();
		ofColor get_dino_color();

		void jump();
		void update_dino_position(float new_x, float new_y);
		void update();
};
