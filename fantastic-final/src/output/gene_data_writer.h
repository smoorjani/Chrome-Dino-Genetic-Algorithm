#pragma once

#include <vector>
#include <fstream>

class gene_data_writer
{
public:
	static void save_data_to_csv(int generation, int individual_number, double fitness_score, std::vector<double> genes);
};


