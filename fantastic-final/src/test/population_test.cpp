#include "catch.hpp"
#include "../src/genetics/population.h"

/*
void selection();
void crossover();
void mutation();
void add_fittest_offspring();
*/

TEST_CASE("Test Initialize Population") {
	population population_;
	int population_size = 6;
	population_.initialize_population(population_size);
	REQUIRE(population_.get_individuals().size() == population_size);
}

TEST_CASE("Test Get Fittest") {
	population population_;
	int population_size = 6;
	population_.initialize_population(population_size);
	
	SECTION("Test Get Fittest") {
		individual temp_individual;
		temp_individual.set_fitness_score(100);
		population_.set_individual(temp_individual, 0);

		REQUIRE(population_.get_fittest() == 0);
	}

	SECTION("Test Get Second Fittest") {
		individual temp_individual;
		temp_individual.set_fitness_score(100);
		population_.set_individual(temp_individual, 0);

		individual second_temp_individual;
		second_temp_individual.set_fitness_score(66);
		population_.set_individual(temp_individual, 3);

		REQUIRE(population_.get_fittest() == 3);
	}
	SECTION("Test Get Least Fittest") {
		individual temp_individual;
		temp_individual.set_fitness_score(-100);
		population_.set_individual(temp_individual, 0);

		REQUIRE(population_.get_fittest() == 0);
	}
}

TEST_CASE("Test AreAllDead") {
	population population_;
	int population_size = 6;
	population_.initialize_population(population_size);

	REQUIRE(!population_.are_all_dead());

	for (int i = 0; i < population_size; i++) {
		individual temp_individual;
		temp_individual.dino_.set_is_dead(true);
		population_.set_individual(temp_individual, i);
	}

	REQUIRE(population_.are_all_dead());
}