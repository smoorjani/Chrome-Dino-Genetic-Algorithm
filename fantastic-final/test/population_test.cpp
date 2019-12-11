#include "catch.hpp"
#include "../src/genetics/population.h"

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
		population_.set_individual(second_temp_individual, 3);

		REQUIRE(population_.get_second_fittest() == 3);
	}
	SECTION("Test Get Least Fittest") {
		individual temp_individual;
		temp_individual.set_fitness_score(-100);
		population_.set_individual(temp_individual, 0);

		REQUIRE(population_.get_least_fit() == 0);
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

TEST_CASE("Test Selection") {
	population population_;
	int population_size = 6;
	population_.initialize_population(population_size);

	individual temp_individual;
	temp_individual.set_fitness_score(100);
	population_.set_individual(temp_individual, 0);

	individual second_temp_individual;
	second_temp_individual.set_fitness_score(66);
	population_.set_individual(second_temp_individual, 3);

	population_.selection();
	REQUIRE(population_.get_fittest() == 0);
	REQUIRE(population_.get_second_fittest() == 3);
}

TEST_CASE("Test Add Fittest Individual") {
	population population_;
	int population_size = 6;
	population_.initialize_population(population_size);

	for (int i = 0; i < population_size - 1; i++) {
		individual temp_individual;
		temp_individual.set_fitness_score((i + 1) * 100);
		population_.set_individual(temp_individual, i);
	}

	population_.selection();
	REQUIRE(population_.get_fittest() == 4);
	REQUIRE(population_.get_least_fit() == 5);

	population_.add_fittest_offspring();
	REQUIRE(population_.get_fittest() == 5);
	REQUIRE(population_.get_individuals()[5].get_genes() == population_.get_individuals()[4].get_genes());
}