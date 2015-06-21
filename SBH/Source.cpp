#include "Source.h"
#include "ACO.h"

int main()
{
	//CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC
	//HIV 240 - actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaattggaggttttatcaaagtaagacagtatgatcagatactcatagaaatctgtggacataaagctataggtacagtattagtaggacctacacctgtcaac
	Sequence *seq = new Sequence("CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC", 8);

	Graph *g = new Graph(seq);

	//g->startSearching();

	//g->printPossibbleSequences();

	ACO *aco = new ACO(seq, 0.5, 20, 0.5, 20);

	aco->getSolution();

	aco->printSequence();
	
	system("pause");
}