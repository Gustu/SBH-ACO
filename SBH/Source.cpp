#include "Source.h"

int main()
{
	Sequence *seq = new Sequence("AGAAAAAA", 3);

	Graph *g = new Graph(seq);
	g->getPossibbleSequences();

	g->printPossibbleSequences();
	system("pause");
}