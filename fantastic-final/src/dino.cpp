#include "dino.h"

const float dino::dino_proportion_scalar = 0.1;

dino::dino() {
	dino_x = DEFAULT_START_X;
	dino_y = DEFAULT_START_Y;

	int window_width = ofGetWindowWidth();
	int window_height = ofGetWindowHeight();
	window_dims.set(window_width, window_height);

	dino_width = window_width * dino_proportion_scalar;
	dino_height = window_height * dino_proportion_scalar;
	dino_hitbox.setSize(dino_width, dino_height);
	dino_hitbox.setPosition(dino_x, dino_y);

	dino_color.set(0,255,0);
}

dino::dino(float x, float y, float width, float height) {
	dino_x = x;
	dino_y = y;

	dino_height = height;
	dino_width = width;
	dino_hitbox.setSize(dino_width, dino_height);
	dino_hitbox.setPosition(dino_x, dino_y);

	dino_color.set(0, 255, 0);
}

float dino::get_dino_x() const {
	return dino_x;
}

float dino::get_dino_y() const {
	return dino_y;
}

float dino::get_dino_width() const {
	return dino_width;
}

float dino::get_dino_height() const {
	return dino_height;
}

float dino::get_velocity_y() const {
	return dino_velocity_y;
}

void dino::set_velocity_y(float y_velocity) {
	this->dino_velocity_y = y_velocity;
}

bool dino::get_is_jumping() const {
	return is_jumping;
}

void dino::set_is_jumping(bool jumping) {
	this->is_jumping = jumping;
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

ofRectangle dino::get_dino_hitbox() {
	return dino_hitbox;
}

ofColor dino::get_dino_color() {
	return dino_color;
}

void dino::jump() {
	if (!this->is_jumping) {
		this->is_jumping = true;
		dino_velocity_y = -JUMP_VELOCITY;
	}
	else {
		this->is_jumping = false;
	}
}

void dino::update_dino_position(float new_x, float new_y) {
	this->dino_x = new_x;
	this->dino_y = new_y;
	dino_hitbox.setPosition(dino_x, dino_y);
}

void dino::update() {
	if (dino_y + dino_velocity_y >= DEFAULT_START_Y) {
		update_dino_position(dino_x, DEFAULT_START_Y);
		set_is_jumping(false);
	}
	else {
		update_dino_position(dino_x, dino_y + dino_velocity_y);
	}
	dino_velocity_y += GRAVITY;
}