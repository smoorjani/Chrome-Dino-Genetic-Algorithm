#include "catch.hpp"
#include "../src/game/obstacle.h"

constexpr int NUMBER_OF_TEST_OBSTACLES = 5;
constexpr float epsilon = .001;

TEST_CASE("Test Setup Obstacle Image") {
	float start_x = 100.54;
	float start_y = 223.23;
	obstacle obstacle_(start_x, start_y);

	std::string file_path = "cactus.png";
	obstacle_.setup_image(file_path);

	REQUIRE(obstacle_.get_obstacle_width() == obstacle_.get_obstacle_hitbox().getWidth());
	REQUIRE(obstacle_.get_obstacle_height() == obstacle_.get_obstacle_hitbox().getHeight());

	REQUIRE(obstacle_.get_obstacle_hitbox().getPosition().x == obstacle_.get_obstacle_x());
	REQUIRE(obstacle_.get_obstacle_hitbox().getPosition().y == obstacle_.get_obstacle_y());
}

TEST_CASE("Test Obstacle Update") {
	float start_x = 100.54;
	float start_y = 223.23;
	obstacle obstacle_(start_x, start_y);

	float initial_velocity = obstacle_.get_velocity_x();
	obstacle_.update(10.1);
	REQUIRE(abs(obstacle_.get_velocity_x() - initial_velocity) - SPEED_FACTOR < epsilon);
}