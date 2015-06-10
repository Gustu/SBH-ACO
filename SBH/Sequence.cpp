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
/* Errors in %  ex. pos = 0.2, neg = 0.2*/
void Sequence::addErrors(double pos, double neg)
{
	srand(time(NULL));
	int length = oligos.size();
	if (length > RAND_MAX){
		cout << "W001: Length higher than RAND_MAX. Errors might be less random." << endl;
	}
	int posErr = (int)(length*pos); // == floor(length*pos)
	int negErr = (int)(length*neg);
	// Lower random oligo class
	for (int i = 0; i < negErr; i++){
		int r = rand() % length;
		OligoClass::OligoEnum oClass = oligos.at(r)->oligoClass->oligoClass;
		if (oClass != OligoClass::OligoEnum::First){
			oligos.at(r)->oligoClass->setOligoClass((oClass - 1) * 2); // lower class
		}
	}
	// Add oligos
	int iOligoSize = pow(4, oligoLength);
	vector<int> tPossibleOligos = createOligoMatrix();
	random_shuffle(tPossibleOligos.begin(), tPossibleOligos.end());
	for (int i = 0; i < posErr; i++){
		int r = rand() % (length * 2); 
		if (r>length){ //if true generate new oligo else change random oligo to class higher
			oligos.push_back(new Oligo());
		}
	}
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
	this->seq = seq->seq;
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

vector<int> Sequence::createOligoMatrix(){
	int iSize = pow(4, oligoLength);
	//A=0,C=1,G=2,T=3
	vector<int> tMatrix;
	for (int i = 0; i < iSize; i++){
		tMatrix.push_back(i);
	}
	for each(Oligo* oligo in oligos){
		tMatrix[oligo->valToLong()] = -1;
	}
	return tMatrix;
}