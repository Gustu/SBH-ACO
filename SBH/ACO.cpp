#include "ACO.h"

double Determinant(double **a, int n);

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

ACO::ACO(Sequence *seq) {
	this->g = new Graph(seq);
	converganceFactor = 0.0;
	weightOfBestSoFarResult = 0.0;
	weightOfBestIterationResult = 1.0;
	weightOfBestRestartResult = 0.0;
	bsUpdate = false;
	pheromons = new double*[g->origSeq->oligos.size()];
	for (int i = 0; i < NUMBER_OF_ANTS; i++) {
		ants.push_back(new Ant(g->origSeq->oligos.size()));
	}
	initWeightOptions();
}

ACO::ACO(Sequence* seq, double learningRate, double numberOfAnts, double initialPheromoneValue) :ACO(seq){
	this->learningRate = learningRate;
	this->numberOfAnts = numberOfAnts;
	this->initialPheromoneValue = initialPheromoneValue;
}

void ACO::initPheromoneValues() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		pheromons[i] = new double[g->origSeq->oligos.size()];
		for (int j = 0; i < g->origSeq->oligos.size(); i++)
			pheromons[i][j] = initialPheromoneValue;
	}
}

bool ACO::satisfiedConditions() {
	return false;
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

void ACO::pheromonesUpdate() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		for (int j = 0; j < g->origSeq->oligos.size(); j++) {
			pheromons[i][j] += learningRate*(getWeightRate(i, j) - pheromons[i][j]);
			if (pheromons[i][j] < 0.01) {
				pheromons[i][j] = 0.01;
			}
			else if (pheromons[i][j] > 0.99) {
				pheromons[i][j] = 0.99;
			}
		}
	}
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
	for (int i = 0; i < size; i++)
	for (int j = 0; j < size; j++)
	if (tau_max - pheromons[i][j] > pheromons[i][j] - tau_min)
		sum += tau_max - pheromons[i][j];
	else
		sum += pheromons[i][j] - tau_min;
	double determinant = Determinant(pheromons, size);
	if (determinant == 0.0)
		exit(EXIT_FAILURE);
	return 2 * (sum / (determinant*(tau_max - tau_min)) - 0.5);
}

double Determinant(double **a, int n)
{
	int i, j, j1, j2;
	double det = 0;
	double **m;

	if (n < 1) { /* Error */

	}
	else if (n == 1) { /* Shouldn't get used */
		det = a[0][0];
	}
	else if (n == 2) {
		det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
	}
	else {
		det = 0;
		for (j1 = 0; j1 < n; j1++) {
			m = new double*[n - 1];
			for (i = 0; i < n - 1; i++)
				m[i] = new double[n - 1];
			for (i = 1; i < n; i++) {
				j2 = 0;
				for (j = 0; j < n; j++) {
					if (j == j1)
						continue;
					m[i - 1][j2] = a[i][j];
					j2++;
				}
			}
			det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * Determinant(m, n - 1);
			for (i = 0; i < n - 1; i++)
				free(m[i]);
			free(m);
		}
	}
	return(det);
}

void ACO::getBestIterationResult(vector<Ant*> ants) {
	vector<Oligo *> temp;
	double rate = 0.0;
	for (Ant * ant : ants) {
		int tempRate = getRate(ant->solution);
		if (tempRate > rate) {
			temp = ant->solution;
			rate = tempRate;
		}
	}
	if (rate > 0.0) {
		bestIterationResult = temp;
	}
}

double ACO::getRate(vector<Oligo*> solution) {
	return 0;
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
		index = 5;
	}

	weightOfBestIterationResult = weightOptions[index][0];
	weightOfBestRestartResult = weightOptions[index][1];
	weightOfBestSoFarResult = weightOptions[index][2];


}

void ACO::resetPheromoneValues() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		for (int j = 0; i < g->origSeq->oligos.size(); i++)
			pheromons[i][j] = INITIAL_PHEROMONE_VALUE;
	}
}

vector<Oligo *> ACO::getSequence() {
	initPheromoneValues();
	while (!satisfiedConditions()) {
		vector<vector<Oligo*>> iterationSolutions;
		for (Ant *ant : ants)
			iterationSolutions.push_back(ant->conctructSolution());
		getBestIterationResult(ants);
		if (bestRestartResult.empty() || getRate(bestIterationResult) > getRate(bestRestartResult)) {
			bestRestartResult = bestIterationResult;
		}
		if (bestSoFarResult.empty() || getRate(bestIterationResult) > getRate(bestSoFarResult)) {
			bestSoFarResult = bestIterationResult;
		}
		pheromonesUpdate();
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