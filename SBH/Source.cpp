#include "Source.h"

int main()
{
	Sequence *seq = new Sequence("ATTCGATTGTCA", 5);

	Graph *g = new Graph(seq);
	g->startSearching();

	g->printPossibbleSequences();
	system("pause");
}