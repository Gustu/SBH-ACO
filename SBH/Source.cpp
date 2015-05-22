#include "Sequence.h"

using namespace std;

int main()
{
	Sequence *seq = new Sequence("AGATGCTGTTAAGCTG", 3);
	seq->adjacent();
	seq->printAdjacenyMatrix();
	seq->printOligos();
	system("pause");
}