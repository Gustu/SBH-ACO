#ifndef Sequence_h
#define Sequence_h

#include <vector>
#include <ctime>
#include <cmath>
#include "Oligo.h"

using namespace std;

class Sequence
{
public:
	string seq;
	int oligoLength;
	int **adjacencyMatrix;
	int errorOligos;
	Oligo* first;
	vector<Oligo *> oligos;

	int** initAdjacencyMatrix(int size);

	Sequence(Sequence *seq);

	vector<Oligo*> oligoFromSequence();

	void adjacent();

	void randomizeOligosSequence();

	void addErrors(double pos, double neg);
	Sequence(string seq, int oligoLength, double neg, double pos);
	void printAdjacenyMatrix();

	void printOligos();

	friend int ** initAdjacencyMatrix(int size);



private:
	vector<int> createOligoMatrix();
};

#endif