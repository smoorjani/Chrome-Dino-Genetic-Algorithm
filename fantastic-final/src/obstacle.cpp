#include "obstacle.h"

const float obstacle::obstacle_proportion_scalar = 0.05;
constexpr int SCREEN_OFFSET = 3000;

obstacle::obstacle(float x, float y) {
	obstacle_x = x;
	obstacle_y = y;
	obstacle_x_velocity = OBSTACLE_VELOCITY;

	int window_width = ofGetWindowWidth();
	int window_height = ofGetWindowHeight();
	window_dims.set(window_width, window_height);

	obstacle_width = obstacle_proportion_scalar * window_width;
	obstacle_height = obstacle_proportion_scalar * window_height;
	obstacle_hitbox.setSize(obstacle_width, obstacle_height);
	obstacle_hitbox.setPosition(obstacle_x, obstacle_y);

	std::string file_path = "cactus.png";
	setup_image(file_path);
	
	obstacle_color.set(255,0,0);
}

obstacle::obstacle(float x, float y, float width, float height) {
    obstacle_x = x;
    obstacle_y = y;

    obstacle_width = width;
    obstacle_height = height;
	obstacle_hitbox.setSize(obstacle_width, obstacle_height);
	obstacle_hitbox.setPosition(obstacle_x, obstacle_y);

	obstacle_color.set(255, 0, 0);
}

float obstacle::get_obstacle_x() const {
	return obstacle_x;
}

float obstacle::get_obstacle_y() const {
	return obstacle_y;
}

float obstacle::get_obstacle_width() const {
	return obstacle_width;
}

float obstacle::get_obstacle_height() const {
	return obstacle_height;
}

float obstacle::get_velocity_x() const {
	return obstacle_x_velocity;
}

void obstacle::set_velocity_x(float x_velocity) {
	this->obstacle_x_velocity = x_velocity;
}

ofRectangle obstacle::get_obstacle_hitbox() {
	return obstacle_hitbox;
}

ofColor obstacle::get_obstacle_color() {
	return obstacle_color;
}

ofImage obstacle::get_obstacle_image() {
	return obstacle_image;
}

void obstacle::set_obstacle_image(ofImage& img) {
	this->obstacle_image = img;
	obstacle_width = obstacle_image.getWidth();
	obstacle_height = obstacle_image.getHeight();
	obstacle_hitbox.setSize(obstacle_width, obstacle_height);
}

void obstacle::setup_image(std::string& filepath) {
	obstacle_image.loadImage(filepath);
	set_obstacle_image(obstacle_image);
}

void obstacle::update_obstacle_position(float new_x, float new_y) {
	this->obstacle_x = new_x;
	this->obstacle_y = new_y;
	obstacle_hitbox.setPosition(obstacle_x, obstacle_y);
}

void obstacle::update(float previous_obstacle_x) {
	if (obstacle_x < 0) {
		// TODO fix random cacti showing up
		int new_obstacle_x = previous_obstacle_x + (rand() % SCREEN_OFFSET) + 200;
		while (new_obstacle_x < ofGetScreenWidth()) {
			new_obstacle_x = previous_obstacle_x + (rand() % SCREEN_OFFSET) + 200;
		}
		update_obstacle_position(new_obstacle_x, obstacle_y);
	}
	else {
		update_obstacle_position(obstacle_x - obstacle_x_velocity, obstacle_y);
	}
	obstacle_x_velocity += SPEED_FACTOR;
}