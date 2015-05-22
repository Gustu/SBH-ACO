#ifndef Sequence_h
#define Sequence_h

#include <string>
#include <vector>
#include <algorithm>
#include "Oligo.h"
#include <iostream>

using namespace std;

class Sequence
{
public:
	string seq;
	int oligoLength;
	int **adjacencyMatrix;
	Oligo* first;
	vector<Oligo *> oligos;

	Sequence(string seq, int oligoLength);

	vector<Oligo*> oligoFromSequence();

	void adjacent();

	void randomizeOligosSequence();

	void addErrors(double pos, double neg);

	void printAdjacenyMatrix();

	void printOligos();

	friend int ** initAdjacencyMatrix(int size);

private:

};

#endif