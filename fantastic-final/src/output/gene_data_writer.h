#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "../genetics/individual.h"

constexpr int FITNESS_INDEX = 2;

class gene_data_writer
{
public:
	static void save_data_to_csv(int generation, int individual_number, double fitness_score, std::vector<double> genes);
	static std::vector<double> get_best_individual_genes(std::string filename);
	static std::vector<double> string_to_vector(std::string line);
};


