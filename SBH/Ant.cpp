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

void Ant::cleanSpeactrum(Oligo* oligo, map<string, int> indexes, int size) {
	if (spectrum[oligo->val].counter >(spectrum[oligo->val].max + 1)) {
		spectrum.erase(spectrum.find(oligo->val));
		// @DOWN USUWANIE KANDYDATOW, KTORZY JUZ OSIAGNELI MAKSA WG. KLASOWOSCI
		for (int i = 0; i < size; i++)
			pheromons[i][indexes[oligo->val]] = 0.0;
	}
}

vector<Oligo*> Ant::conctructSolution(Graph *g, map<string, int> indexes) {
	reset();
	Oligo *next = g->first->oligo;
	generateSpectrum(g); // generuje spektrum mozliwych oligo do wyboru
	solution.push_back(next);
	spectrum[next->val].counter++;
	int oligoLength = g->origSeq->oligoLength;
	int desiredLength = g->origSeq->seq.size();
	while (oligoLength*solution.size() - currentOverlap < desiredLength) {
		cleanSpeactrum(next, indexes, g->origSeq->oligos.size()); // usuwamy ze spektrum to co zwiekszylo klasowosc o 2
		int beforeIndex = indexes[next->val];
		next = chooseNext(next, indexes, g->origSeq->oligos);
		spectrum[next->val].counter++;
		currentOverlap += adjacencyMatrix[beforeIndex][indexes[next->val]];
		solution.push_back(next);
	}
	cutSolution(oligoLength, desiredLength); // skracamy rozwiazanie o 1 oligo, jesli jest za dlugie
	//updatePheromons(g, currentOverlap, indexes);
	return solution;
}

Oligo * Ant::chooseNext(Oligo *oligo, map<string, int> indexes, vector<Oligo *> &oligos) {
	vector<int> candidates; // lista indeksow do kandydatow
	vector<double> pheromonList; // lista kandydatow
	int index = indexes[oligo->val];
	for (int i = 0; i < size; i++) {
		if (index != i && pheromons[index][i]>0) {
			candidates.push_back(i);
			pheromonList.push_back(pheromons[index][i]);
		}
	}
	Roulette *roulette = new Roulette(pheromonList, pheromonList.size());
	int nr = roulette->spin(); // losujemy na podstawie listy feromonow
	return oligos[candidates[nr]];
}

void Ant::updatePheromons(Graph *g, int overlap, map<string, int> indexes) {
	int length = solution.size()*g->origSeq->oligoLength - overlap;
	double pheromonValue = static_cast<double>(length) / g->origSeq->seq.size();
	for (int i = 0; i < solution.size() - 1; i++) {
		pheromonsToAdd[indexes[solution[i]->val]][indexes[solution[i + 1]->val]] = pheromonValue;
	}
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