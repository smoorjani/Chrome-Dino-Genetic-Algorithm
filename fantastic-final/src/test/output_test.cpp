#include "catch.hpp"
#include "../output/gene_data_writer.h"

TEST_CASE("Test Get Best Individual Genes") {
	std::string file_name = "data.csv";
	std::vector<double> best_genes = gene_data_writer::get_best_individual_genes(file_name);

	std::vector<double> expected_genes = {-2,-1.9129,8.84732,2.28675};
	REQUIRE(best_genes == expected_genes);
}

TEST_CASE("Test String to Vector") {
	std::string test_string = "-2,-1.9129,8.84732,2.28675";
	std::vector<double> test_vector = gene_data_writer::string_to_vector(test_string);

	std::vector<double> expected_vector = {-2,-1.9129,8.84732,2.28675};
	REQUIRE(test_vector == expected_vector);
}