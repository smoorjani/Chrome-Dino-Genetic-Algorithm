#pragma once

#include <ctime>
#include <cstdlib>
#include <vector>
#include <ostream>
#include "../dino.h"

constexpr int GENE_LENGTH = 7;

class individual
{
	private:
		double fitness_score;
		std::vector<double> genes;

	public:
		individual();
		dino dino_;

		void increment_score(double points);
		void set_fitness_score(int score);
		double get_fitness_score();

		std::vector<double> get_genes();
		void set_gene(double value, int index);

		bool should_jump(std::vector<obstacle> obstacles);

		individual& operator=(individual* rhs);
		friend std::ostream& operator<<(std::ostream& output, individual& individual);
};

