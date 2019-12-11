#include "population.h"

// Fill individuals with a user-specified amount of individuals
void population::initialize_population(int population_size) {
	individuals.reserve(population_size);

	for (size_t i = 0; i < population_size; i++) {
		individual temp;
		individuals.push_back(temp);
	}
}

individual population::get_individual(int index) {
	return individuals[index];
}

int population::get_fittest() {
	int max_fitness_score = INT_MIN;
	int max_fitness_index = 0;

	for (size_t i = 0; i < individuals.size(); i++) {
		if (max_fitness_score <= individuals[i].get_fitness_score()) {
			max_fitness_score = individuals[i].get_fitness_score();
			max_fitness_index = i;
		}
	}

	return max_fitness_index;
}

int population::get_second_fittest() {
	int max_fitness = get_fittest();
	int second_max_fitness = 0;
	int second_max_fitness_score = INT_MIN;

	for (size_t i = 0; i < individuals.size(); i++) {
		if (i != max_fitness && individuals[i].get_fitness_score() > second_max_fitness_score) {
			second_max_fitness_score = individuals[i].get_fitness_score();
			second_max_fitness = i;
		}
	}

	return second_max_fitness;
}

int population::get_least_fit() {
	int min_fitness_value = INT_MAX;
	int min_fitness_index = 0;

	for (size_t i = 0; i < individuals.size(); i++) {
		if (min_fitness_value >= individuals[i].get_fitness_score()) {
			min_fitness_value = individuals[i].get_fitness_score();
			min_fitness_index = i;
		}
	}

	return min_fitness_index;
}

void population::set_individual(individual individual, int index) {
	individuals[index] = individual;
}

std::vector<individual> population::get_individuals() {
	return individuals;
}

void population::clear() {
	individuals.clear();
}

bool population::are_all_dead() {
	for (auto& individual : individuals) {
		if (!individual.dino_.get_is_dead()) {
			return false;
		}
	}
	return true;
}

// Finds the fittest and second fittest individuals
void population::selection() {
	fittest_individual = get_fittest();
	second_fittest_individual = get_second_fittest();
}

// Swaps genes between two fittest to take best traits from both
void population::crossover() {
	int crossover_index = rand() % GENE_LENGTH;

	for (int i = 0; i < crossover_index; i++) {
		int temp = individuals[fittest_individual].get_genes()[i];
		individuals[fittest_individual].set_gene(individuals[second_fittest_individual].get_genes()[i], i);
		individuals[second_fittest_individual].set_gene(temp, i);
	}
}

// Randomly mutates a random gene to simulate mutations in a population
void population::mutation() {
	for (int i = 0; i < NUM_MUTATIONS; i++) {
		int mutation_index = rand() % GENE_LENGTH;
		int individual_to_mutate = int(rand() % individuals.size());
		double random_mutation_value = float((rand()) / float(RAND_MAX / GENE_RANGE)) - (GENE_RANGE/2);

		while (abs(random_mutation_value + individuals[individual_to_mutate].get_genes()[mutation_index]) > GENE_RANGE) {
			random_mutation_value = float((rand()) / float(RAND_MAX / GENE_RANGE)) - (GENE_RANGE/2);
			// Dampen mutations as individual gets closer to desirable traits
			random_mutation_value /= abs(individuals[individual_to_mutate].get_fitness_score());
		}

		individuals[individual_to_mutate].set_gene((individuals[individual_to_mutate].get_genes()[mutation_index]) + random_mutation_value, mutation_index);
	}
}

// Replaces worst individual witht hte fittest
void population::add_fittest_offspring() {
	int least_fittest_index = get_least_fit();
	set_individual(get_individual(fittest_individual), least_fittest_index);
}