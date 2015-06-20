#ifndef ANT_H
#define ANT_H

#define INITIAL_PHEROMONE_VALUE 0.5
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
	vector<Oligo*> conctructSolution(Graph* g, map<string, int> indexes);	
	vector<Oligo*> solution;
	double **pheromonsToAdd;
private:
	int **adjacencyMatrix;
	double **pheromons;
	
	int currentOverlap;
	double initialPheromoneValue;
	int size;
	map<string, Bounds> spectrum;	
	void cutSolution(int oligoLength, int desiredLength);
	void generateSpectrum(Graph* g);
	void cleanSpeactrum(Oligo* oligo, map<string, int> indexes, int size);

	Oligo* chooseNext(Oligo* oligo, map<string, int> indexes, vector<Oligo*>& oligos);
	void updatePheromons(Graph* g, int overlap, map<string, int> indexes);

	void reset();
};

#endif