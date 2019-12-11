#pragma once
#include "individual.h"

constexpr int NUM_MUTATIONS = 2;

class population
{
	private:
		int fittest_individual = 0;
		int second_fittest_individual = 0;

	public:
		std::vector<individual> individuals;

		void initialize_population(int population_size);

		int get_fittest();
		int get_second_fittest();
		int get_least_fit();

		individual get_individual(int index);
		void set_individual(individual individual, int index);
		void clear();

		std::vector<individual> get_individuals();
		bool are_all_dead();

		void selection();
		void crossover();
		void mutation();
		void add_fittest_offspring();
};

