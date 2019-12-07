#include "catch.hpp"
#include "../src/obstacle.h"

constexpr int NUMBER_OF_TEST_OBSTACLES = 5;


/*
void setup_image(std::string& filepath);
void update();
*/

TEST_CASE("Test Setup Image") {
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

TEST_CASE("Test Update") {

}