#include "catch.hpp"
#include "../src/dino.h"
#include "../src/obstacle.h"

constexpr int NUMBER_OF_TEST_OBSTACLES = 5;
constexpr float dino_hitbox_shrink_scalar = 0.4;

TEST_CASE("Test Get Nearest Obstacle Functions") {
	dino dino_;
	std::vector<obstacle> obstacles_;

	for (int obstacle_num = 0; obstacle_num < NUMBER_OF_TEST_OBSTACLES; obstacle_num++) {
		obstacle temp_ob(obstacle_num * 100,DEFAULT_START_Y);
		obstacles_.push_back(temp_ob);
	}

	SECTION("Nearest Obstacle") {
		int nearest = dino_.get_nearest_obstacle(obstacles_);
		REQUIRE(nearest == 0);
	}

	SECTION("Second Nearest Obstacle") {
		int second_nearest = dino_.get_second_nearest_obstacle(obstacles_);
		REQUIRE(second_nearest == 1);
	}
}

TEST_CASE("Test Has Collided") {
	dino dino_;
	std::vector<obstacle> obstacles_;

	for (int obstacle_num = 0; obstacle_num < NUMBER_OF_TEST_OBSTACLES; obstacle_num++) {
		obstacle temp_ob(obstacle_num * 100, DEFAULT_START_Y);
		obstacles_.push_back(temp_ob);
	}

	SECTION("No Collisions") {
		for (int obstacle_num = 0; obstacle_num < NUMBER_OF_TEST_OBSTACLES; obstacle_num++) {
			REQUIRE(!dino_.has_collided(obstacles_[obstacle_num]));
		}
	}

	SECTION("Collision") {
		obstacle new_obstacle(dino_.get_dino_x(), dino_.get_dino_y());
		REQUIRE(dino_.has_collided(new_obstacle));
	}
}

TEST_CASE("Test Setup Image") {
	dino dino_;

	std::string file_path = "big_chrome_dino.png";
	dino_.setup_image(file_path);

	REQUIRE(dino_.get_dino_width() == dino_.get_dino_image().getWidth() * dino_hitbox_shrink_scalar);
	REQUIRE(dino_.get_dino_height() == dino_.get_dino_image().getHeight());

	REQUIRE(dino_.get_dino_hitbox().getPosition().x == dino_.get_dino_x() + (2 * dino_.get_dino_width() * dino_hitbox_shrink_scalar));
	REQUIRE(dino_.get_dino_hitbox().getPosition().y == dino_.get_dino_y());
}

TEST_CASE("Test Jump") {
	dino dino_;

	REQUIRE(!dino_.get_is_jumping());
	dino_.jump();
	REQUIRE(dino_.get_is_jumping());
}

TEST_CASE("Test Update Dino Position") {
	dino dino_;

	float new_dino_x = 20.5;
	float new_dino_y = 100.812;
	dino_.update_dino_position(new_dino_x, new_dino_y);

	REQUIRE(dino_.get_dino_x() == 20.5);
	REQUIRE(dino_.get_dino_y() == 100.812);
}

TEST_CASE("Test Update") {

}

TEST_CASE("Test Reset") {
	dino dino_;
	float new_dino_x = 20.5;
	float new_dino_y = 100.812;
	float new_velocity_y = 5.3;

	dino_.update_dino_position(new_dino_x, new_dino_y);
	dino_.set_velocity_y(new_velocity_y);
	REQUIRE(dino_.get_dino_x() == new_dino_x);
	REQUIRE(dino_.get_dino_y() == new_dino_y);
	REQUIRE(dino_.get_velocity_y() == new_velocity_y);

	dino_.set_is_dead(true);
	dino_.set_is_jumping(true);
	REQUIRE(dino_.get_is_jumping());
	REQUIRE(dino_.get_is_dead());

	dino_.reset();
	REQUIRE(dino_.get_dino_x() == DEFAULT_START_X);
	REQUIRE(dino_.get_dino_y() == DEFAULT_START_Y);
	REQUIRE(dino_.get_velocity_y() == 0);

	REQUIRE(!dino_.get_is_jumping());
	REQUIRE(!dino_.get_is_dead());
}