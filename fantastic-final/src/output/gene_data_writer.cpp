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