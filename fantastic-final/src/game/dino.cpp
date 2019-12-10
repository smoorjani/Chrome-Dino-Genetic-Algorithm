#include "dino.h"

const float dino::dino_proportion_scalar = 0.1;
constexpr float dino_hitbox_shrink_scalar = 0.35;

dino::dino(std::string &dino_img) {
	dino_x = DEFAULT_START_X;
	dino_y = DEFAULT_START_Y;
	dino_velocity_y = 0;

	is_jumping = false;
	is_dead = false;

	// Bases initial hitbox size on the window's proportions
	dino_hitbox.setPosition(dino_x, dino_y);

	dino_color.set(155,255,0);
	setup_image(dino_img);
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

bool dino::get_is_dead() const {
	return is_dead;
}

void dino::set_is_dead(bool dead) {
	this->is_dead = dead;
}

ofRectangle dino::get_dino_hitbox() {
	return dino_hitbox;
}

ofColor dino::get_dino_color() {
	return dino_color;
}

ofImage dino::get_dino_image() {
	return dino_image;
}

int dino::get_nearest_obstacle(std::vector<obstacle> obstacles) {
	int nearest_index = 0;
	// changed to depend on obstacle.h
	int nearest_distance = 5000;

	for (int obstacle_index = 0; obstacle_index < obstacles.size(); obstacle_index++) {
		if (abs(obstacles[obstacle_index].get_obstacle_x() - get_dino_x()) < nearest_distance) {
			nearest_distance = int(abs(obstacles[obstacle_index].get_obstacle_x() - get_dino_x()));
			nearest_index = obstacle_index;
		}
	}

	return nearest_index;
}

int dino::get_second_nearest_obstacle(std::vector<obstacle> obstacles) {
	int nearest_index = get_nearest_obstacle(obstacles);
	int second_nearest_index = 0;
	int nearest_distance = 5000;

	for (int obstacle_index = 0; obstacle_index < obstacles.size(); obstacle_index++) {
		if (obstacle_index != nearest_index && abs(obstacles[obstacle_index].get_obstacle_x() - get_dino_x()) < nearest_distance) {
			nearest_distance = int(abs(obstacles[obstacle_index].get_obstacle_x() - get_dino_x()));
			second_nearest_index = obstacle_index;
		}
	}

	return second_nearest_index;
}

bool dino::has_collided(obstacle &rhs) {
	return (dino_hitbox.getX() < rhs.get_obstacle_hitbox().getX() + rhs.get_obstacle_hitbox().getWidth() &&
		dino_hitbox.getX() + dino_hitbox.getWidth() > rhs.get_obstacle_hitbox().getX() &&
		dino_hitbox.getY() < rhs.get_obstacle_hitbox().getY() + rhs.get_obstacle_hitbox().getHeight() &&
		dino_hitbox.getY() + dino_hitbox.getHeight() > rhs.get_obstacle_hitbox().getY());
}

void dino::set_dino_image(ofImage &img) {
	this->dino_image = img;
	dino_width = dino_image.getWidth() * dino_hitbox_shrink_scalar;
	dino_height = dino_image.getHeight();
	dino_hitbox.setSize(dino_width, dino_height);
	dino_hitbox.setPosition(dino_x + (2 * dino_width * dino_hitbox_shrink_scalar), dino_y);
}

void dino::setup_image(std::string &file_path) {
	// Maybe add try/catch?
	dino_image.loadImage(file_path);
	set_dino_image(dino_image);
}

void dino::jump() {
	if (!get_is_jumping()) {
		this->is_jumping = true;
		dino_velocity_y = -JUMP_VELOCITY;
	}
}

void dino::update_dino_position(float new_x, float new_y) {
	this->dino_x = new_x;
	this->dino_y = new_y;
	dino_hitbox.setPosition(dino_x + (2 * dino_width * dino_hitbox_shrink_scalar), dino_y);
}

void dino::update() {
	if (dino_y + dino_velocity_y > DEFAULT_START_Y) {
		update_dino_position(dino_x, DEFAULT_START_Y);
		this->is_jumping = false;
	}
	else {
		update_dino_position(dino_x, dino_y + dino_velocity_y);
	}
	dino_velocity_y += GRAVITY;
}

void dino::reset() {
	dino_x = DEFAULT_START_X;
	dino_y = DEFAULT_START_Y;
	dino_velocity_y = 0;

	is_jumping = false;
	is_dead = false;
}