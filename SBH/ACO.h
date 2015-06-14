#ifndef ACO_H
#define ACO_H
#include "Graph.h"
#include "Ant.h"

/*
* PDF z opisem algorytmu http://www.researchgate.net/publication/222836939_An_ant_colony_optimization_algorithm_for_DNA_sequencing_by_hybridization
*/

#define INITIAL_PHEROMONE_VALUE 0.5


class ACO {
public:
	vector<Oligo *> bestSoFarResult;
	vector<Oligo *> bestIterationResult;
	vector<Oligo *> bestRestartResult;
	double **pheromons;
	double converganceFactor; //  a measure of how far the algorithm is from convergence
	bool bsUpdate; //it becomes true when the algorithm reaches convergence
	vector<Ant*> ants;
	Graph *g;
	// TODO - NEED TO ADD PHEROMONS!!!
	ACO(Sequence *seq);

	void initPheromoneValues();
	bool satisfiedConditions();
	void pheromonesUpdate();
	
	double computeConverganceFactor();
	void resetPheromoneValues();
	vector<Oligo *> getSequence();
	void getBestIterationResult(vector<Ant*> vector); // maximaizes solution rate
	double getRate(vector<Oligo*> solution); // rates solution - needed to compare
	friend double Determinant(double** pheromons, int size);
};


#endif