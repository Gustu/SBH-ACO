#ifndef ACO_H
#define ACO_H
#include "Graph.h"
#include "Ant.h"

/*
* PDF z opisem algorytmu http://www.researchgate.net/publication/222836939_An_ant_colony_optimization_algorithm_for_DNA_sequencing_by_hybridization
*/

#define NUMBER_OF_ANTS 20


class ACO {
public:
	
	double initialPheromoneValue;
	
	ACO(Sequence* seq, double learningRate, int numberOfAnts, double initialPheromoneValue);
	
	vector<Oligo *> getSequence();

private:
	vector<Oligo *> bestSoFarResult;
	vector<Oligo *> bestIterationResult;
	vector<Oligo *> bestRestartResult;
	double **pheromons;
	int numberOfAnts;
	double learningRate;
	double converganceFactor; //  a measure of how far the algorithm is from convergence
	bool bsUpdate; //it becomes true when the algorithm reaches convergence
	vector<Ant*> ants;
	Graph *g;
	double **weightOptions;
	void initWeightOptions();
	void initIndexMap();
	ACO(Sequence *seq);
	void initPheromoneValues(); // initializes pheromons matrix with initial value
	bool satisfiedConditions(); // decides if algorithm can stop
	double isIn(int i, int j, vector<Oligo*> result); // decides if oligo is in solution
	double getWeightRate(int i, int j); // gets weight proportional rate
	void pheromonesUpdate(); // updates pheromons matrix
	double computeConverganceFactor();
	void resetPheromoneValues();
	void updateWeights();
	int compareSolutions(vector<Oligo*> vec1, vector<Oligo*> vec2); // 1 vec1 > vec2, 0 vec1 == vec2, -1 vec1 < vec2
	// updates solution weights if convergance factor has changed interval
	void getBestIterationResult(vector<Ant*> ants); // maximaizes solution rate
	friend double Determinant(double** pheromons, int size); // computes matrix determinant
	double weightOfBestSoFarResult;
	double weightOfBestIterationResult;
	double weightOfBestRestartResult;
	map<string, int> indexes;
};


#endif