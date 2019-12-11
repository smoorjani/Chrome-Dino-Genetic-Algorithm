#include "catch.hpp"
#include "../src/genetics/individual.h"
#include "../src/game/obstacle.h"

TEST_CASE("Test Score Altering Methods") {
	individual individual_;
	double temp_double = 10.5;

	SECTION("Test Incremement Score") {
		REQUIRE(individual_.get_fitness_score() == 0);
		individual_.increment_score(temp_double);
		REQUIRE(individual_.get_fitness_score() == temp_double);
	}

	SECTION("Test Decrease Score") {
		REQUIRE(individual_.get_fitness_score() == 0);
		individual_.decrease_score(temp_double);
		REQUIRE(individual_.get_fitness_score() == -temp_double);
	}
}

TEST_CASE("Test Should Jump") {
	individual individual_;
	std::vector<obstacle> obstacles_;

	obstacles_.push_back(obstacle(50, 50));
	for (int i = 1; i < MAX_NUMBER_OF_OBSTACLES; i++) {
		obstacles_.push_back(obstacle(obstacles_[i - 1].get_obstacle_x() + (rand() % SCREEN_OFFSET) + MIN_DIST_BETWEEN_OBSTACLES, 50));
	}

	for (int i = 0; i < individual_.get_genes().size(); i++) {
		individual_.set_gene(0, i);
	}
	REQUIRE(!individual_.should_jump(obstacles_))
}

TEST_CASE("Test Overloaded Equals Operator") {
	individual individual_;
	individual new_individual_;

	REQUIRE(new_individual_.get_genes() != individual_.get_genes());
	REQUIRE(new_individual_.get_fitness_score() != individual_.get_fitness_score());

	new_individual_ = individual_;
	REQUIRE(new_individual_.get_genes() == individual_.get_genes());
	REQUIRE(new_individual_.get_fitness_score() == individual_.get_fitness_score());

}