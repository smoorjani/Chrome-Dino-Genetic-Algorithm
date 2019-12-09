#include "gene_data_writer.h"

void gene_data_writer::save_data_to_csv(int generation, int individual_number, double fitness_score, std::vector<double> genes) {
	std::ofstream csv_file;
	csv_file.open("data.csv", std::ofstream::app);

	csv_file << generation << "," << individual_number << "," << fitness_score;
	for (double gene : genes) {
		csv_file << "," << gene;
	}
	csv_file << "\n";

	csv_file.close();
}

std::vector<double> gene_data_writer::get_best_individual_genes(std::string filename) {
	std::ifstream csv_file;
	csv_file.open(filename);

	double current_fitness_score;
	double max_fitness_score = 0;

	std::vector<double> best_genes = {0,0,0,0};

	std::string temp_line;
	std::vector<double> temp_double_vector = {0,0,0,0,0,0,0};

	if (csv_file.is_open()) {
		while (std::getline(csv_file, temp_line, '\n')) {
			temp_double_vector = string_to_vector(temp_line);

			if (temp_double_vector[FITNESS_INDEX] > max_fitness_score) {
				max_fitness_score = temp_double_vector[FITNESS_INDEX];

				for (int i = FITNESS_INDEX + 1; i < temp_double_vector.size(); i++) {
					best_genes[i - (FITNESS_INDEX + 1)] = temp_double_vector[i];
				}
			}
			
		}
	}

	csv_file.close();
	return best_genes;
}

std::vector<double> gene_data_writer::string_to_vector(std::string line)
{
	vector<double> double_vector;
	std::istringstream string_parser(line);
	std::string temp_string;

	while (std::getline(string_parser, temp_string, ',')) {
		double_vector.push_back(std::stod(temp_string));
	}
	return double_vector;
}