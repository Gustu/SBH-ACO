#include "Source.h"

int main()
{
	//CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC
	Sequence *seq = new Sequence("CATGTTTCCACTTACAGATCCTTCA", 5);

	Graph *g = new Graph(seq);

	g->startSearching();

	g->printPossibbleSequences();
	system("pause");
}