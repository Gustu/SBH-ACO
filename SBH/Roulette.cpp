#include "Roulette.h"

void Roulette::smoothing() {
	double min = n[0];
	for (int i = 0; i<size; i++){
		if (n[i] < min)min = n[i];
	}
	for (int i = 0; i<size; i++){
		n[i] = min*(1 + logWithBase(PODSTAWA, n[i] / min));
	}
}

double Roulette::logWithBase(double base, double x) {
	return log(x) / log(base);
}

Roulette::Roulette(vector<double> temp, int size) {
	total = 0;
	this->size = size;
	n = new double[size];
	for (int i = 0; i<size; i++){
		n[i] = temp[i];
	}
	if (!BEZ_WYGLADZANIA)smoothing();
	c = new double[size + 1];
	c[0] = 0;
	for (int i = 0; i < size; i++) {
		c[i + 1] = c[i] + n[i];
		total += n[i];
	}
}

int Roulette::spin() {
	int r = rand() % 10000;
	double random = static_cast<double>(r) / 10000;
	random *= total;
	int a = 0;
	int b = size;
	while (b - a > 1) {
		int mid = (a + b) / 2;
		if (c[mid] > random) b = mid;
		else a = mid;
	}
	return a;
}

Roulette::~Roulette() {
	delete c;
	delete n;
}