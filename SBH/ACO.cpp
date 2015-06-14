#include "ACO.h"

double Determinant(double **a, int n);

ACO::ACO(Sequence *seq) {
	this->g = new Graph(seq);
	converganceFactor = 0.0;
	bsUpdate = false;
	pheromons = new double*[g->origSeq->oligos.size()];
}

void ACO::initPheromoneValues() {
	for (int i = 0; i < g->origSeq->oligos.size(); i++) {
		pheromons[i] = new double[g->origSeq->oligos.size()];
		for (int j = 0; i < g->origSeq->oligos.size(); i++)
			pheromons[i][j] = INITIAL_PHEROMONE_VALUE;
	}
}

bool ACO::satisfiedConditions() {
	return false;
}

void ACO::pheromonesUpdate() {
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
	return 2*(sum/(determinant*(tau_max-tau_min))-0.5);
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
		for (j1 = 0; j1<n; j1++) {
			m = new double*[n - 1];
			for (i = 0; i<n - 1; i++)
				m[i] = new double[n - 1];
			for (i = 1; i<n; i++) {
				j2 = 0;
				for (j = 0; j<n; j++) {
					if (j == j1)
						continue;
					m[i - 1][j2] = a[i][j];
					j2++;
				}
			}
			det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * Determinant(m, n - 1);
			for (i = 0; i<n - 1; i++)
				free(m[i]);
			free(m);
		}
	}
	return(det);
}

void ACO::getBestIterationResult(vector<Ant*> vector) {
}

double ACO::getRate(vector<Oligo*> solution) {
	return 0;
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