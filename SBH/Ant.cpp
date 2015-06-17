#include "Ant.h"

vector<Oligo*> Ant::conctructSolution() {
	vector<Oligo *> temp;
	return temp;
}

Ant::Ant(int size) {
	pheromons = new double*[size];
	for (int i = 0; i < size; i++) {
		pheromons[i] = new double[size];
		for (int j = 0; j < size; j++) {
			pheromons[i][j] = INITIAL_PHEROMONE_VALUE;
		}
	}
}