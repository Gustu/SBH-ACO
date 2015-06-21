#include "ACO.h"
#include <iostream>
#include <string>

void ACO::initWeightOptions() {
	double temp[5][3] = {
		{ 1, 0, 0 },
		{ 2.0 / 3.0, 1.0 / 3.0, 0.0 },
		{ 1.0 / 3.0, 2.0 / 3.0, 0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
	};
	weightOptions = new double*[5];
	for (int i = 0; i < 5; i++) {
		weightOptions[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			weightOptions[i][j] = temp[i][j];
			;
		}
	}
}

void ACO::initIndexMap() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		indexes[g->origSeq->oligos[i]->val] = i;
	}
}

ACO::ACO(Sequence* seq, double learningRate, int numberOfAnts, double initialPheromoneValue, int numberOfIterations){
	this->learningRate = learningRate;
	this->numberOfAnts = numberOfAnts;
	this->initialPheromoneValue = initialPheromoneValue;
	this->numberOfIterations = numberOfIterations;
	this->g = new Graph(seq);
	iteration = 0;
	converganceFactor = 0.0;
	weightOfBestSoFarResult = 0.0;
	weightOfBestIterationResult = 1.0;
	weightOfBestRestartResult = 0.0;
	bsUpdate = false;
	initIndexMap();
	pheromons = new double*[g->origSeq->oligos.size()];
	initPheromoneValues();
	for (int i = 0; i < numberOfAnts; i++) {
		ants.push_back(new Ant(g->origSeq->oligos.size(), g->origSeq->adjacencyMatrix, this->initialPheromoneValue));
	}
	initWeightOptions();
}

void ACO::printPheromons() {
	cout << "####" << endl;
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		for (int j = 0; j < g->origSeq->oligos.size(); j++) {
			cout << pheromons[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "####" << endl;
}

void ACO::initPheromoneValues() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		pheromons[i] = new double[g->origSeq->oligos.size()];
		for (int j = 0; j < g->origSeq->oligos.size(); j++) {
			if (g->origSeq->adjacencyMatrix[i][j] > 0) {
				pheromons[i][j] = initialPheromoneValue;
			}
			else {
				pheromons[i][j] = 0.0;
			}
		}
	}
}

bool ACO::satisfiedConditions() {
	if (iteration++ < numberOfIterations) {
		return false;
	}
	else {
		return true;
	}
}

void ACO::vaporize() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		for (int j = 0; j < g->origSeq->oligos.size(); j++) {
			pheromons[i][j] *= 1 - learningRate;
		}
	}
}

void ACO::pheromonesUpdate() {
	for (Ant *ant : ants) {
		for (int i = 0; i < g->origSeq->oligos.size(); i++) {
			for (int j = 0; j < g->origSeq->oligos.size(); j++) {
				pheromons[i][j] += ant->pheromonsToAdd[i][j];
			}
		}
	}
	vaporize();
}


void ACO::getBestIterationResult() {
	vector<Oligo *> temp = ants[0]->solution;
	for (Ant * ant : ants) {
		if (compareSolutions(temp, ant->solution) == 1) {
			temp = ant->solution;
		}
	}
	bestIterationResult = temp;
}


// Returns 1 if vec1 > vec2
// Returns 0 if vec1 == vec2
// Returns -1 if vec1 < vec2
int ACO::compareSolutions(vector<Oligo*> vec1, vector<Oligo*> vec2) {

	int overlapVec1 = 0;
	int overlapVec2 = 0;
	for (int i = 0; i < vec1.size() - 1; i++) {
		overlapVec1 += g->origSeq->adjacencyMatrix[indexes[vec1[i]->val]][indexes[vec1[i + 1]->val]];
		
	}
	for (int i = 0; i < vec2.size() - 1; i++) {
		overlapVec2 += g->origSeq->adjacencyMatrix[indexes[vec2[i]->val]][indexes[vec2[i + 1]->val]];
	}
	
	if (vec1.size() * g->origSeq->oligoLength - overlapVec1 < vec2.size() * g->origSeq->oligoLength - overlapVec2) {
		return 1;
	}
	else if (vec1.size() * g->origSeq->oligoLength - overlapVec1 == vec2.size() * g->origSeq->oligoLength - overlapVec2) {
		return 0;
	}
	else {
		return -1;
	}


}

void ACO::resetPheromoneValues() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		for (int j = 0; i < g->origSeq->oligos.size(); i++) {
			if (g->origSeq->adjacencyMatrix[i][j] > 0) {
				pheromons[i][j] = initialPheromoneValue;
			}
		}
	}
}

vector<Oligo *> ACO::getSolution() {
	//printPheromons();
	while (!satisfiedConditions()) {
		for (Ant *ant : ants) {
			ant->conctructSolution(g);
		}
		getBestIterationResult();
		pheromonesUpdate();
		//printPheromons();
	}
	return bestIterationResult;
}

void ACO::printSequence() {

	string sSeq = bestIterationResult[0]->val; // Clean sequence from *seq ex. ACGTTTTT
	for each (Oligo * oligo in bestIterationResult)
	{
		int i = 0;
		while (sSeq.substr(sSeq.size() - oligo->val.size() + i, sSeq.size()) != oligo->val.substr(0, oligo->val.size() - i) && i<oligo->val.size()) {
			i++;
		}
		if (i > 0 && i < oligo->val.size()) {
			sSeq += oligo->val.substr(oligo->val.size() - i, oligo->val.size());
			//cout << oligo->val << "." << oligo->oligoClass->oligoClass << "->";
		}
	}

	int same = 0;
	for (int i = 0; i < sSeq.size(); i++){
		if (sSeq[i] == g->origSeq->seq[i]){
			same++;
		}
	}
	cout << "#####" << endl;
	cout << "seq length: " << sSeq.size() << endl;
	cout << same << "/" << g->origSeq->seq.size() << "[" << (int)((same * 100) / g->origSeq->seq.size()) << "%]\t" << endl;
	cout << sSeq << endl;
	cout << "#####" << endl;

}