#include "Source.h"

int main()
{
	//CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC
	Sequence *seq = new Sequence("CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTT", 8);

	Graph *g = new Graph(seq);

	g->startSearching();

	g->printPossibbleSequences();
	
	system("pause");
}