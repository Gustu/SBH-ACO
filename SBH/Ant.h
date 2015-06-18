#ifndef ANT_H
#define ANT_H

#define INITIAL_PHEROMONE_VALUE 0.5

class Oligo;
#include <vector>

using namespace std;

class Ant {
public:
	vector<Oligo*> conctructSolution();
	double **pheromons;
	int currentOverlap;
	vector<Oligo*> solution;
	Ant(int size);
};

#endif