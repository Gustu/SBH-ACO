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

double ACO::isIn(int i, int j, vector<Oligo*> result) {
	vector<Oligo *>::iterator it;
	if (i != 0 && j != 0) {
		it = find(result.begin(), result.end(), g->origSeq->oligos[i]);
		if (it != result.end()) {
			++it;
			if (it != result.end() && (*it)->val == g->origSeq->oligos[j]->val) {
				return 1.0;
			}
		}
	}
	else if (i == 0 && j != 0) {
		if (result[0]->val == g->origSeq->oligos[j]->val) {
			return 1.0;
		}
	}
	else if (i != 0 && j == 0) {
		if (result[result.size() - 1]->val == g->origSeq->oligos[i]->val) {
			return 1.0;
		}
	}
	return 0.0;
}

double ACO::getWeightRate(int i, int j) {
	return weightOfBestIterationResult*isIn(i, j, bestIterationResult)
		+ weightOfBestRestartResult*isIn(i, j, bestRestartResult)
		+ weightOfBestSoFarResult*isIn(i, j, bestSoFarResult);
}

void ACO::lu(double** A, int n) {

	int i, j, k;

	for (k = 0; k < n - 1; k++)
	{
		if (fabs(A[k][k]) < DBL_EPSILON) exit(EXIT_FAILURE);
		for (i = k + 1; i < n; i++)
			A[i][k] /= A[k][k];
		for (i = k + 1; i < n; i++)
		for (j = k + 1; j < n; j++)
			A[i][j] -= A[i][k] * A[k][j];
	}


}

void ACO::pheromonesUpdate() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		for (int j = 0; j < g->origSeq->oligos.size(); j++) {
			pheromons[i][j] += learningRate*(getWeightRate(i, j) - pheromons[i][j]);
			if (pheromons[i][j] > 0 && pheromons[i][j] < 0.01) {
				pheromons[i][j] = 0.01;
			}
			else if (pheromons[i][j] > 0.99) {
				pheromons[i][j] = 0.99;
			}
		}
	}
}

double ACO::Determinant2(double** pheromons, int size) {
	double **u;
	u = new double*[size];
	for (int i = 0; i < size; i++) {
		u[i] = new double[size];
		for (int j = 0; j < size; j++) {
			u[i][j] = pheromons[i][j];
		}
	}
	lu(u, size);
	double det = 1.0;
	for (int i = 0; i < size; i++) {
		det *= u[i][i];
		cout << i << " " << i << " " << u[i][i] << "#";
	}
	return det;
}

double ACO::computeConverganceFactor() {
	double tau_max = -1;
	double tau_min = pheromons[0][0];
	int size = g->origSeq->oligos.size();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tau_max < pheromons[i][j])
				tau_max = pheromons[i][j];
			if (tau_min > pheromons[i][j])
				tau_min = pheromons[i][j];
		}
	}

	double sum = 0.0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tau_max - pheromons[i][j] > pheromons[i][j] - tau_min)
				sum += tau_max - pheromons[i][j];
			else
				sum += pheromons[i][j] - tau_min;
		}
	}


	double determinant = Determinant2(pheromons, size);
	return 2 * (sum / (determinant*(tau_max - tau_min)) - 0.5);
}

double Deteminant2(double **pheromons, int size);

void lu(double **a, double **l, double **u, int n);

void ACO::getBestIterationResult(vector<Ant*> ants) {
	vector<Oligo *> temp = ants[0]->solution;
	for (Ant * ant : ants) {
		if (compareSolutions(temp, ant->solution) == -1) {
			temp = ant->solution;
		}
	}
	bestIterationResult = temp;
}

void ACO::updateWeights() {
	int index;
	if (!bsUpdate) {
		if (converganceFactor < 0.7) {
			index = 0;
		}
		else if (converganceFactor >= 0.7 && converganceFactor < 0.9) {
			index = 1;
		}
		else if (converganceFactor >= 0.9 && converganceFactor < 0.95) {
			index = 2;
		}
		else {
			index = 3;
		}
	}
	else {
		index = 4;
	}

	weightOfBestIterationResult = weightOptions[index][0];
	weightOfBestRestartResult = weightOptions[index][1];
	weightOfBestSoFarResult = weightOptions[index][2];


}

// Returns 1 if vec1 > vec2
// Returns 0 if vec1 == vec2
// Returns -1 if vec1 < vec2
int ACO::compareSolutions(vector<Oligo*> vec1, vector<Oligo*> vec2) {
	if (vec1.size() > vec2.size()) {
		return 1;
	}
	else if (vec1.size() == vec2.size()) {
		int overlapVec1 = 0;
		int overlapVec2 = 0;
		for (int i = 0; i < vec1.size() - 1; i++) {
			overlapVec1 += g->origSeq->adjacencyMatrix[indexes[vec1[i]->val]][indexes[vec1[i + 1]->val]];
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
	while (!satisfiedConditions()) {
		vector<vector<Oligo*>> iterationSolutions;
		for (Ant *ant : ants)
			iterationSolutions.push_back(ant->conctructSolution(g, indexes));
		getBestIterationResult(ants);
		if (bestRestartResult.empty() || (compareSolutions(bestIterationResult, bestRestartResult) == 1)) {
			bestRestartResult = bestIterationResult;
		}
		if (bestSoFarResult.empty() || (compareSolutions(bestIterationResult, bestSoFarResult) == 1)) {
			bestSoFarResult = bestIterationResult;
		}
		pheromonesUpdate();
		printPheromons();
		converganceFactor = computeConverganceFactor();
		updateWeights();
		if (converganceFactor > 0.9999) {
			if (bsUpdate) {
				resetPheromoneValues();
				bestRestartResult.clear();
				bsUpdate = false;
			}
			else {
				bsUpdate = true;
			}
		}
	}
	return bestSoFarResult;
}

vector<Oligo *> ACO::getSolution2() {
	while (!satisfiedConditions()) {
		vector<vector<Oligo*>> iterationSolutions;
		for (Ant *ant : ants)
			iterationSolutions.push_back(ant->conctructSolution(g, indexes));
		getBestIterationResult(ants);
		if (bestRestartResult.empty() || (compareSolutions(bestIterationResult, bestRestartResult) == 1)) {
			bestRestartResult = bestIterationResult;
		}
		if (bestSoFarResult.empty() || (compareSolutions(bestIterationResult, bestSoFarResult) == 1)) {
			bestSoFarResult = bestIterationResult;
		}
		//printPheromons();
		pheromonesUpdate();
		//printPheromons();
	}
	return bestSoFarResult;
}

void ACO::printSequence() {

	string sSeq = bestSoFarResult[0]->val; // Clean sequence from *seq ex. ACGTTTTT
	for each (Oligo * oligo in bestSoFarResult)
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