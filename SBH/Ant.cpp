#include "Ant.h"
#include "Roulette.h"
#include <map>
#include "Oligo.h"
#include "Graph.h"
#include <iostream>

void Ant::cutSolution(int oligoLength, int desiredLength) {
	if (oligoLength*solution.size() - currentOverlap > desiredLength) {
		solution.pop_back();
	}
}

void Ant::generateSpectrum(Graph* g) {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		Bounds bound;
		bound.max = g->origSeq->oligos[i]->oligoClass->baseOligoClass + 1;
		bound.min = g->origSeq->oligos[i]->oligoClass->baseOligoClass - 1;
		bound.counter = 0;
		spectrum[g->origSeq->oligos[i]->val] = bound;
	}
}

void Ant::cleanSpeactrum(Oligo* oligo) {
	if (spectrum[oligo->val].counter >(spectrum[oligo->val].max + 1)) {
		spectrum.erase(spectrum.find(oligo->val));
	}
}

vector<Oligo*> Ant::conctructSolution(Graph *g, map<string, int> indexes) {
	reset();
	Oligo *next = g->first->oligo;
	generateSpectrum(g);
	solution.push_back(next);
	spectrum[next->val].counter++;
	int oligoLength = g->origSeq->oligoLength;
	int desiredLength = g->origSeq->seq.size();
	while (oligoLength*solution.size() - currentOverlap < desiredLength) {
		cleanSpeactrum(next);
		int before = indexes[next->val];
		next = chooseNext(next, indexes, g->origSeq->oligos);
		currentOverlap += adjacencyMatrix[before][indexes[next->val]];
		solution.push_back(next);
	}
	cutSolution(oligoLength, desiredLength);
	return solution;
}

Oligo * Ant::chooseNext(Oligo *oligo, map<string, int> indexes, vector<Oligo *> &oligos) {
	vector<int> candidates;
	vector<double> pheromonList;
	int index = indexes[oligo->val];
	map<string, int>::iterator it;
	for (int i = 0; i < size; i++) {
		if (index != i && pheromons[index][i]>0) {
			candidates.push_back(i);
			pheromonList.push_back(pheromons[index][i]);
		}
	}
	Roulette *roulette = new Roulette(pheromonList, pheromonList.size());
	int nr = roulette->spin();
	return oligos[candidates[nr]];
}

Ant::Ant(int size, int **adjacenecyMatrix, double initialPheromoneValue) {
	this->initialPheromoneValue = initialPheromoneValue;
	this->adjacencyMatrix = adjacenecyMatrix;
	this->size = size;
	pheromons = new double*[size];
	for (int i = 0; i < size; i++) {
		pheromons[i] = new double[size];
		for (int j = 0; j< size; j++) {
			if (adjacencyMatrix[i][j] > 0) {
				pheromons[i][j] = initialPheromoneValue;
			}
		}
	}
}

void Ant::reset() {
	solution.clear();
	currentOverlap = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (adjacencyMatrix[i][j] > 0) {
				pheromons[i][j] = initialPheromoneValue;
			}
		}
	}

}