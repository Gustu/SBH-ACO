#ifndef ANT_H
#define ANT_H

#include <map>
#include "Graph.h"

class Oligo;
#include <vector>

using namespace std;

struct Bounds {
	int min;
	int max;
	int counter;
};

class Ant {
public:
	Ant(int size, int **adjacenecyMatrix, double initialPheromoneValue);
	void multiplePheromons(int size, double rate);
	double getErrorRatio(Graph* g);
	void rateSolution(int size, int length, int desiredLength, Graph* g, double overlapRatio);
	void addToPheromons(int before, int index);
	void conctructSolution(Graph* g, int bestOverlap);
	int chooseNext(int index, int size);
	vector<Oligo*> solution;
	double **pheromonsToAdd;
private:
	int **adjacencyMatrix;
	double **pheromons;
	
	int currentOverlap;
	double initialPheromoneValue;
	int size;
	map<string, Bounds> spectrum;	
	int cutSolution(int oligoLength, int desiredLength);
	void generateSpectrum(Graph* g);
	int findIndexOfFirstOligo(Graph* g, Oligo* next);

	void reset();
};

#endif