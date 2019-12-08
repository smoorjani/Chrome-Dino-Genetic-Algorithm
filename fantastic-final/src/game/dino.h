#pragma once
#include "obstacle.h"
#include <cmath>

constexpr float DEFAULT_START_X = 40;
constexpr float DEFAULT_START_Y = 400;
constexpr float GRAVITY = 0.5;
constexpr float JUMP_VELOCITY = 13.5;

class dino {
	private:
		float dino_x;
		float dino_y;
		float dino_velocity_y;
		float dino_width;
		float dino_height;

		bool is_jumping;
		bool is_dead;

		ofVec2f window_dims;
		static const float dino_proportion_scalar;

		ofImage dino_image;
		ofRectangle dino_hitbox;
		ofColor dino_color;

	public:
		dino();

		float get_dino_x() const;
		float get_dino_y() const;
		float get_dino_width() const;
		float get_dino_height() const;

		float get_velocity_y() const;
		void set_velocity_y(float y_velocity);

		bool get_is_jumping() const;
		void set_is_jumping(bool jumping);
		bool get_is_dead() const;
		void set_is_dead(bool dead);

		int get_nearest_obstacle(std::vector<obstacle> obstacles);
		int get_second_nearest_obstacle(std::vector<obstacle> obstacles);

		bool has_collided(obstacle& rhs);

		ofRectangle get_dino_hitbox();
		ofColor get_dino_color();
		
		ofImage get_dino_image();
		void set_dino_image(ofImage &img);
		void setup_image(std::string &file_path);

		void jump();
		void update_dino_position(float new_x, float new_y);
		void update();
		void reset();
};
