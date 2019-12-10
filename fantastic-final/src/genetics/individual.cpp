#include "individual.h"

individual::individual() {
	std::vector<double> temp_genes(GENE_LENGTH, 0);

	for (int i = 0; i < GENE_LENGTH; i++) {
		temp_genes[i] = float((rand()) / float(RAND_MAX / GENE_RANGE)) - (GENE_RANGE/2);
	}

	genes = temp_genes;
	fitness_score = 0;
}

void individual::increment_score(double points) {
	fitness_score += points;
}

void individual::decrease_score(double points) {
	fitness_score -= points;
}

void individual::set_fitness_score(int score) {
	this->fitness_score = score;
}

double individual::get_fitness_score() {
	return fitness_score;
}

std::vector<double> individual::get_genes() {
	return genes;
}

void individual::set_gene(double value, int index) {
	genes[index] = value;
}

bool individual::should_jump(std::vector<obstacle> obstacles) {
	// Multiply all weights with values
	//	- Velocity of nearest obstacle
	//	- Distance to nearest obstacle
	//	- Length of nearest obstacle
	// Last weight acts as a bias

	int nearest_obstacle_index = dino_.get_nearest_obstacle(obstacles);

	double nearest_obstacle_velocity = abs(obstacles[nearest_obstacle_index].get_velocity_x());
	int distance_to_nearest_obstacle = abs(obstacles[nearest_obstacle_index].get_obstacle_x() - dino_.get_dino_x());
	int nearest_obstacle_length = obstacles[nearest_obstacle_index].get_obstacle_width();

	double computed_gradient = genes[0] * nearest_obstacle_velocity + genes[1] * distance_to_nearest_obstacle 
							 + genes[2] * nearest_obstacle_length + genes[3];

	// Apply activation function
	//	- Relu (if positive)
	//	- Subtracted a constant to ensure dino should jump
	//  - Constant determined by tolerance factor

	return std::max(0.0, computed_gradient - ((GENE_RANGE/2) * DECISION_TOLERANCE));
}

individual& individual::operator=(individual* rhs) {
	this->fitness_score = rhs->fitness_score;
	this->genes = rhs->genes;
	return *this;
}

// Overloaded output to streamline display of values
std::ostream& operator<<(std::ostream& output, individual& individual) {
	output << "Fitness: " << individual.get_fitness_score() << " Genes: ";

	for (size_t i = 0; i < individual.get_genes().size(); i++) {
		output << individual.get_genes()[i] << " ";
	}
	output << "\n";

	return output;
}


//	- Velocity of nearest and second nearest obstacles
	//	- Distance to nearest obstacle / length of nearest obstacle
	//	- Distance to second nearest obstacle / length of second nearest obstacle
/*
	int nearest_obstacle_index = dino_.get_nearest_obstacle(obstacles);
	int second_nearest_obstacle_index = dino_.get_second_nearest_obstacle(obstacles);

	double nearest_obstacle_velocity = abs(obstacles[nearest_obstacle_index].get_velocity_x());
	double second_nearest_obstacle_velocity = abs(obstacles[second_nearest_obstacle_index].get_velocity_x());
	int distance_to_nearest_obstacle = abs(obstacles[nearest_obstacle_index].get_obstacle_x() - dino_.get_dino_x());
	int nearest_obstacle_length = obstacles[nearest_obstacle_index].get_obstacle_width();
	int distance_to_second_nearest_obstacle = abs(obstacles[second_nearest_obstacle_index].get_obstacle_x() - dino_.get_dino_x());
	int second_nearest_obstacle_length = obstacles[second_nearest_obstacle_index].get_obstacle_width();

	double computed_gradient = genes[0] * nearest_obstacle_velocity + genes[1] * second_nearest_obstacle_velocity +
							   genes[2] * distance_to_nearest_obstacle + genes[3] * distance_to_second_nearest_obstacle +
							   genes[4] * nearest_obstacle_length + genes[5] * second_nearest_obstacle_length +
							   genes[6];

	*/