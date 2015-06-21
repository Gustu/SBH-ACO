#include "Ant.h"
#include "Roulette.h"
#include <map>
#include "Oligo.h"
#include "Graph.h"
#include <iostream>

int Ant::cutSolution(int oligoLength, int desiredLength) {
	int length = oligoLength*solution.size() - currentOverlap;
	if (length > desiredLength) {
		solution.pop_back();
		length -= oligoLength;
	}
	return length;
}

void Ant::generateSpectrum(Graph* g) {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		Bounds bound;
		int oligoClass = g->origSeq->oligos[i]->oligoClass->baseOligoClass;
		if (oligoClass == 0) {
			bound.max = 0;
			bound.min = 0;
		}
		else if (oligoClass == 1) {
			bound.max = 2;
			bound.min = 1;
		}
		else if (oligoClass == 2) {
			bound.max = 4;
			bound.min = 3;
		}
		else {
			bound.min = 5;
			bound.max = 0xFFFFFF;
		}
		bound.counter = 0;
		spectrum[g->origSeq->oligos[i]->val] = bound;
	}
}

int Ant::findIndexOfFirstOligo(Graph* g, Oligo* next) {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		if (g->origSeq->oligos[i]->val == next->val) {
			return i;
		}
	}
	return -1;
}

void Ant::conctructSolution(Graph *g, int bestOverlap) {
	reset();
	generateSpectrum(g);
	Oligo *next = g->first->oligo;
	int index = findIndexOfFirstOligo(g, next);
	int before;
	if (index == -1) {
		return;
	}
	solution.push_back(next);

	int oligoLength = g->origSeq->oligoLength;
	int desiredLength = g->origSeq->seq.size();

	while (oligoLength*solution.size() - currentOverlap < desiredLength) {
		before = index;
		index = chooseNext(index, g->origSeq->oligos.size());
		solution.push_back(g->origSeq->oligos[index]);
		currentOverlap += g->origSeq->adjacencyMatrix[before][index];
		if (oligoLength*solution.size() - currentOverlap <= desiredLength)
			addToPheromons(before, index);
		else {
			currentOverlap -= g->origSeq->adjacencyMatrix[before][index];
		}
	}
	int length = cutSolution(oligoLength, desiredLength);
	//cout << currentOverlap << endl;
	rateSolution(g->origSeq->oligos.size(), length, desiredLength, g, static_cast<double>(currentOverlap)/bestOverlap);
}

int Ant::chooseNext(int index, int size) {
	vector<int> candidates; // lista indeksow do kandydatow
	vector<double> pheromonList; // lista kandydatow
	for (int i = 0; i < size; i++) {
		if (index != i && pheromons[index][i]>0) {
			candidates.push_back(i);
			pheromonList.push_back(pheromons[index][i]);
		}
	}
	Roulette *roulette = new Roulette(pheromonList, pheromonList.size());
	int nr = roulette->spin(); // losujemy na podstawie listy feromonow
	return candidates[nr];
}

Ant::Ant(int size, int **adjacenecyMatrix, double initialPheromoneValue) {
	this->initialPheromoneValue = initialPheromoneValue;
	this->adjacencyMatrix = adjacenecyMatrix;
	this->size = size;
	pheromons = new double*[size];
	pheromonsToAdd = new double*[size];
	for (int i = 0; i < size; i++) {
		pheromons[i] = new double[size];
		pheromonsToAdd[i] = new double[size];
		for (int j = 0; j< size; j++) {
			pheromonsToAdd[i][j] = 0.0;
			if (adjacencyMatrix[i][j] > 0) {
				pheromons[i][j] = initialPheromoneValue;
			}
		}
	}
}

void Ant::multiplePheromons(int size, double rate) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (pheromonsToAdd[i][j] == 1) {
				pheromonsToAdd[i][j] *= rate;
			}
		}
	}
}

double Ant::getErrorRatio(Graph *g) {
	spectrum[solution[0]->val].counter++;
	for (int i = 0; i < solution.size() - 1; i++) {
		Edge *edge = new Edge(new Node(solution[i]), new Node(solution[i + 1]));
		edge->getBetweenOligos(g->origSeq->oligoLength);
		spectrum[solution[i + 1]->val].counter++;
		for (Oligo *oligo : edge->oligos) {
			spectrum[solution[i]->val].counter++;
		}
	}
	int counter = 0;
	for (map<string, Bounds>::iterator it = spectrum.begin(); it != spectrum.end(); ++it) {
		int over = (*it).second.counter - (*it).second.max;
		int below = (*it).second.min - (*it).second.counter;
		if (over > 0) {
			counter += over;
		}
		if (below > 0) {
			counter += below;
		}
	}

	return 1.0 / counter;
}

void Ant::rateSolution(int size, int length, int desiredLength, Graph *g, double overlapRatio) {
	double rate;
	if (overlapRatio > 1) {
		rate = initialPheromoneValue;
	}
	else rate = initialPheromoneValue * overlapRatio;
	double errorRatio = getErrorRatio(g);
	rate *= (1 - errorRatio);
	multiplePheromons(size, rate);
}

void Ant::addToPheromons(int before, int index) {
	pheromonsToAdd[before][index] = 1;
}

void Ant::reset() {
	solution.clear();
	currentOverlap = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (adjacencyMatrix[i][j] > 0) {
				pheromons[i][j] = initialPheromoneValue;
			}
			else {
				pheromons[i][j] = 0.0;
			}
		}
	}

}