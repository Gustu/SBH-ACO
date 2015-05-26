#include "Source.h"

int main()
{
	Sequence *seq = new Sequence("ATTCGTTTAGCTATAA", 3);

	Graph *g = new Graph(seq);
	g->startSearching();

	g->printPossibbleSequences();
	system("pause");
}