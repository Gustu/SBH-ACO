#include "ACO.h"

ACO::ACO(Sequence *seq) {
	this->g = new Graph(seq);
	converganceFactor = 0.0;
	bsUpdate = false;
}

void ACO::initPheromoneValues() {
}

bool ACO::satisfiedConditions() {
	return false;
}

void ACO::pheromonesUpdate() {
}

double ACO::computeConverganceFactor() {
	return 0;
}

void ACO::getBestIterationResult(vector<Ant*> vector) {
}

double ACO::getRate(vector<Oligo*> bestIterationResult) {
	return 0;
}

void ACO::resetPheromoneValues() {
}

vector<Oligo *> ACO::getSequence() {
	initPheromoneValues();
	while (!satisfiedConditions()) {
		vector<vector<Oligo*>> iterationSolutions;
		int c = 0;
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