#include "Source.h"

int main()
{
	Sequence *seq = new Sequence("CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC", 8);

	Graph *g = new Graph(seq);

	g->startSearching();

	g->printPossibbleSequences();
	system("pause");
}