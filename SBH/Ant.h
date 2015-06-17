#ifndef ANT_H
#define ANT_H

#define INITIAL_PHEROMONE_VALUE 0.5

class Oligo;
#include <vector>
#include <algorithm>

using namespace std;

class Ant {
public:
	vector<Oligo*> conctructSolution();
	double **pheromons;
	vector<Oligo*> solution;
	Ant(int size);
};

#endif