#ifndef ACO_H
#define ACO_H
#include "Graph.h"
#include "Ant.h"

/*
* PDF z opisem algorytmu http://www.researchgate.net/publication/222836939_An_ant_colony_optimization_algorithm_for_DNA_sequencing_by_hybridization
*/


class ACO {
public:
	
	double initialPheromoneValue;
	
	ACO(Sequence* seq, double learningRate, int numberOfAnts, double initialPheromoneValue, int numberOfIterations);

	void printPheromons();
	vector<Oligo*> getSolution();
	void printSequence();
	int bestOverlap;
	int iterationOverlap;
private:
	vector<Oligo *> bestSoFarResult;
	vector<Oligo *> bestOverlapResult;
	vector<Oligo *> bestIterationResult;
	vector<Oligo *> bestRestartResult;
	double **pheromons;
	int numberOfAnts;
	int numberOfIterations;
	double learningRate;
	double converganceFactor; //  a measure of how far the algorithm is from convergence
	bool bsUpdate; //it becomes true when the algorithm reaches convergence
	vector<Ant*> ants;
	Graph *g;
	int iteration;
	double **weightOptions;
	void initWeightOptions();
	void initIndexMap();
	void initPheromoneValues(); // initializes pheromons matrix with initial value
	bool satisfiedConditions(); // decides if algorithm can stop
	void vaporize();
	void pheromonesUpdate();

	// updates pheromons matrix

	void resetPheromoneValues();

	int compareSolutions(vector<Oligo*> vec1, vector<Oligo*> vec2); // 1 vec1 > vec2, 0 vec1 == vec2, -1 vec1 < vec2
	// updates solution weights if convergance factor has changed interval
	void getBestIterationResult(); // maximaizes solution rate
	friend double Determinant(double** pheromons, int size); // computes matrix determinant
	double weightOfBestSoFarResult;
	double weightOfBestIterationResult;
	double weightOfBestRestartResult;
	map<string, int> indexes;
};


#endif