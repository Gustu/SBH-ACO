#include "Source.h"

using namespace std;

vector<Oligo*> Sequence::oligoFromSequence() {
	vector<Oligo*> vec;
	for (unsigned int i = 0; i < seq.length() - oligoLength + 1; i++)
	{
		Oligo *oligo = new Oligo(seq.substr(i, oligoLength));
		bool test = false;
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i]->val == oligo->val) {
				vec[i]->baseQuantity++;
				vec[i]->oligoClass->setOligoClass(vec[i]->baseQuantity);
				test = true;
				break;
			}
		}
		if(!test)
			vec.push_back(oligo);
	}
	oligos = vec;
	return vec;
}

void Sequence::adjacent() {
	int size = this->oligos.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j) {
				adjacencyMatrix[i][j] = oligoLength;
			}
			else {
				for (int k = 0; k < oligoLength - 1; k++)
				{
					if (oligos[i]->val.substr(k + 1, oligoLength - (k + 1)) == oligos[j]->val.substr(0, oligoLength - (k + 1))){
						adjacencyMatrix[i][j] = oligoLength - (k + 1);
						break;
					}						
				}
			}
		}
	}
}

void Sequence::randomizeOligosSequence() {	
	first = oligos[0];
	random_shuffle(oligos.begin(), oligos.end());
}

void Sequence::addErrors(double pos, double neg)
{
}

Sequence::Sequence(string seq, int oligoLength) {
	this->seq = seq;
	this->oligoLength = oligoLength;
	int oligoNumber = (seq.length() - oligoLength + 1);
	if (oligoNumber < 1) {
		cout << "Error: bad oligo length" << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	this->adjacencyMatrix = initAdjacencyMatrix(seq.length() - oligoLength + 1);
	oligoFromSequence();
	randomizeOligosSequence();
	adjacent();
}

Sequence::Sequence(Sequence *seq) {
	this->adjacencyMatrix = seq->adjacencyMatrix;
	this->first = seq->first;
	this->oligoLength = seq->oligoLength;
	this->oligos = seq->oligos;
}

int ** Sequence::initAdjacencyMatrix(int size) {
	int **t = new int*[size];
	for (int i = 0; i < size; i++)
	{
		t[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			t[i][j] = 0;
		}
	}

	return t;
}

void Sequence::printAdjacenyMatrix(){
	for (int i = 0; i < seq.length() - oligoLength + 1; i++)
	{
		for (int j = 0; j < seq.length() - oligoLength + 1; j++)
		{
			cout << adjacencyMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Sequence::printOligos() {
	for each (Oligo* oligo in oligos)
	{
		cout << oligo->val << " ";
	}
	cout << endl;
}