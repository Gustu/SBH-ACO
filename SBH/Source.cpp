#include "Source.h"
#include "ACO.h"
#include <ctime>

using namespace std;

//#define ACCURATE_ALGORITHM
#define ACO_ALGORITHM

int main()
{
	srand(time(NULL));
	//CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC
	//HIV 240 - actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaattggaggttttatcaaagtaagacagtatgatcagatactcatagaaatctgtggacataaagctataggtacagtattagtaggacctacacctgtcaac
	Sequence *seq = new Sequence("CATGTTTCCACTTACAGATCCTTCAAAAAGAGTGTTTCAAAACTGCTCTATGAAAAGGAATGTTCAACTCTGTGAGTTAAATAAAAGCATCAAAAAAAAGTTTCTGAGAATGCTTCTGTC", 8, 0, 0);

#ifdef ACCURATE_ALGORITHM
	Graph *g = new Graph(seq);	
	clock_t begin2 = clock();
	g->startSearching();
	clock_t end2 = clock();
	double elapsed_secs2 = double(end2 - begin2) / CLOCKS_PER_SEC;

	cout << "Time elapsed secs: " << elapsed_secs2 << endl;

	g->printPossibbleSequences();
#endif

#ifdef ACO_ALGORITHM
	ACO *aco = new ACO(seq, 0.7, 10, 0.5, 60);

	clock_t begin = clock();

	aco->getSolution();

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Time elapsed secs: " << elapsed_secs << endl;

	aco->printSequence();
#endif
	
	system("pause");
}