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
	string seqs[4][5] = {
			{
				"agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaaga",
				"gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgctt",
				"cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtaca",
				"cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaattt",
				"actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtatta"
			}, {
				"agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcgggg",
				"gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgcttttgaacccaaaagaactttgacttaggctataaagacacacccctcccca",
				"cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtacagtgacggggactggccagcagagggcgccgaaagctcactgtgggacccg",
				"cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaatttatatcggaatttaaattgaaattgttactgtaatcatacctggtttgttt",
				"actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaat"
			}, {
				"agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcggggcactcatctttcagcaagcctgggactggccactctccagtctctggctg",
				"gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgcttttgaacccaaaagaactttgacttaggctataaagacacacccctccccaaacttgctctaacacagccttcaatggagtccaacacaatatagataagt",
				"cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtacagtgacggggactggccagcagagggcgccgaaagctcactgtgggacccgcctttgcttttcaggatggtgagtttttttgttttttcgttgtgtgtttt",
				"cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaatttatatcggaatttaaattgaaattgttactgtaatcatacctggtttgtttcagagccatatcaccaagatagagaacaacctaggtctccggagggggca",
				"actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaattggaggttttatcaaagtaagacagtatgatcagatactcatagaaatct"
			}, {
				"agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcggggcactcatctttcagcaagcctgggactggccactctccagtctctggctgccaggcagccctctggaccccctgtgcctggtgaccctgcatgggagtgg",
				"gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgcttttgaacccaaaagaactttgacttaggctataaagacacacccctccccaaacttgctctaacacagccttcaatggagtccaacacaatatagataagtgggaaagatactcggaaacttcaaagtccctgaaaaataatgacaattat",
				"cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtacagtgacggggactggccagcagagggcgccgaaagctcactgtgggacccgcctttgcttttcaggatggtgagtttttttgttttttcgttgtgtgtttttttggtttgctttttgtttttaacttttattgaagtatagtcgatttaaa",
				"cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaatttatatcggaatttaaattgaaattgttactgtaatcatacctggtttgtttcagagccatatcaccaagatagagaacaacctaggtctccggagggggcaagggcatcagtgtgctcagttgaaaatcccttgtcaacatctaggcctta",
				"actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaattggaggttttatcaaagtaagacagtatgatcagatactcatagaaatctgtggacataaagctataggtacagtattagtaggacctacacctgtcaac"
			}
	};
	/*
	agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaaga
	gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgctt
	cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtaca
	cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaattt
	actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtatta
	agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcgggg
	gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgcttttgaacccaaaagaactttgacttaggctataaagacacacccctcccca
	cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtacagtgacggggactggccagcagagggcgccgaaagctcactgtgggacccg
	cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaatttatatcggaatttaaattgaaattgttactgtaatcatacctggtttgttt
	actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaat
	agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcggggcactcatctttcagcaagcctgggactggccactctccagtctctggctg
	gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgcttttgaacccaaaagaactttgacttaggctataaagacacacccctccccaaacttgctctaacacagccttcaatggagtccaacacaatatagataagt
	cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtacagtgacggggactggccagcagagggcgccgaaagctcactgtgggacccgcctttgcttttcaggatggtgagtttttttgttttttcgttgtgtgtttt
	cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaatttatatcggaatttaaattgaaattgttactgtaatcatacctggtttgtttcagagccatatcaccaagatagagaacaacctaggtctccggagggggca
	actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaattggaggttttatcaaagtaagacagtatgatcagatactcatagaaatct
	agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcggggcactcatctttcagcaagcctgggactggccactctccagtctctggctgccaggcagccctctggaccccctgtgcctggtgaccctgcatgggagtgg
	gatctttattcaccttttaaccacatattttgtcatcaaaatgagttttgaccatgcagattcaacatttcttacaaacacattatgcttttgaacccaaaagaactttgacttaggctataaagacacacccctccccaaacttgctctaacacagccttcaatggagtccaacacaatatagataagtgggaaagatactcggaaacttcaaagtccctgaaaaataatgacaattat
	cctgcatcctgagactggccctcagactgaaggagccccttctgcggggcytcccactcacaggcgggcgtccccgtacctacacrtacagtgacggggactggccagcagagggcgccgaaagctcactgtgggacccgcctttgcttttcaggatggtgagtttttttgttttttcgttgtgtgtttttttggtttgctttttgtttttaacttttattgaagtatagtcgatttaaa
	cggacacacaaaaagaaagaagaatttttaggatcttttgtgtgcgaataactatgaggaagattaataattttcctctcattgaaatttatatcggaatttaaattgaaattgttactgtaatcatacctggtttgtttcagagccatatcaccaagatagagaacaacctaggtctccggagggggcaagggcatcagtgtgctcagttgaaaatcccttgtcaacatctaggcctta
	actctttggcaacgacccctcgtcacaataaagataggggggcaactaaaggaagctctattagatacaggagcagatgatacagtattagaagaaatgagtttgccaggaagatggaaaccaaaaatgatagggggaattggaggttttatcaaagtaagacagtatgatcagatactcatagaaatctgtggacataaagctataggtacagtattagtaggacctacacctgtcaac
	*/
	double elapsed_secs2 = 0;
	double elapsed_secs = 0;
	int oligoLength = 8;
	double neg = 0.1;
	double pos = 0.1;
	//Sequence *seq = new Sequence("agctcccaggatgcccggtccatctctctctctggccctggtgctgtcggccatgggggctctgctgaggccagggacccccagggaagaagtcttcagcacctcagccttgcccagggagcaggccacaggcagcggggcactcatctttcagcaagcctgggactggccactctccagtctctggctgccaggcagccctctggaccccctgtgcctggtgaccctgcatgggagtggcaacgggagcagggcccccctgcgggtggtgggggtcctgagcagctacgagcaggccttcctggaggctgtgcggcgcacccactggggcctgagtgacttgaccaccttcgcagtgtgccccgctggcaacgggcagcctgtgctgccccacctgcagcggctgcaggcatggctgggggagcccggggggcggtggctggtggtcctgcacctggaggaagtgacgtgggagccaacacccttgctgaggttccaggagcctccgcctggaggagccagccccccagagctggcgctgctggtggtgtacccagggcctggcctggaggtcactgtcaccggggctgggctacctggcacccagagcctctgcctgaccgcggactcggacttcctggccttggtcgtggaccacccggagggggcctggcgccggcctgggttagcccttaccctgcggcgccgtggaaatggtgcgctcctgagcactgcccagctgcaggcgctgctgttcggtgcggactcccgctgcttcacacgaaagaccccagccctgttactcttgctgccggcccggtcttcggcaccgatgcccgcgcacggtcggctggacttggtgcccttcccgcagcccagggcttccccggagccagaggaggcaccgcccagcgctgatcccttcctggagactctcacgcgcctggtgcgcgcgcttgcgggacccccggcccgagcctcgccaccgcggctggccttggacccgggcgcactggctggtttcccgcagggccaggtcaacctgtcggaccccgcggccctggagcgcctgctggacgg", oligoLength, neg, pos);
	vector<Sequence *> sequences;
	for (int i = 0; i < 5; i++) {
		
	}	
	sequences.push_back(new Sequence(seqs[3][0], oligoLength, neg, pos));
	for (Sequence *seq : sequences){
		cout << "next" << endl;
#ifdef ACCURATE_ALGORITHM
		Graph *g = new Graph(seq);
		clock_t begin2 = clock();
		g->startSearching();
		clock_t end2 = clock();
		elapsed_secs2 += double(end2 - begin2) / CLOCKS_PER_SEC;
		//cout << "Time elapsed secs: " << elapsed_secs2 << endl;	

		g->printPossibbleSequences();
		delete g;
#endif

#ifdef ACO_ALGORITHM
		//ACO *aco = new ACO(seq, 0.7, 10, 0.5, 20);
		ACO *aco = new ACO(seq, 0.7, 10, 0.5, 20);

		clock_t begin = clock();

		aco->getSolution();

		clock_t end = clock();
		elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
		//cout << "Time elapsed secs ACO: " << elapsed_secs << endl;
		aco->printSequence();
		delete aco;
		

		
#endif
	}

	cout << "Time elapsed secs: " << elapsed_secs2/5 << endl;
	cout << "Time elapsed secs ACO: " << elapsed_secs/5 << endl;
	
	system("pause");
}