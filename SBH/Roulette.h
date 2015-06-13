#ifndef ROULETTE_H
#define ROULETTE_H
#include <random>

using namespace std;

//WYGLADZANIE FEROMONOW
//podstawa logarytmu
#define PODSTAWA 2
//0 z wygladzaniem, 1 - bez wygladzania
#define BEZ_WYGLADZANIA 0


class Roulette {
public:
	double *c;
	double total;
	double *n;
	int size;
	void smoothing();

	double logWithBase(double base, double x);

	Roulette(vector<double> temp, int size);

	int spin();

	~Roulette();
};

#endif
