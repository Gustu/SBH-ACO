#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Sequence.h"
#include <map>
#include "Edge.h"
#include <list>

class Graph
{
public:
	Node *first;
	Sequence *origSeq;
	vector< vector<Oligo *> > possibbleSequences;
	vector<Oligo *> pSeq;
	map<string, int> oligoMap;
	int seqLength;
	list<string> result;
	int test;
	int stack;

	vector<Edge *> getAdjacencyEdges(Node *node);
	void getPossibbleSequences(Node* node, int errors, int weigth);
	void printPossibbleSequences();
	void startSearching();
	void setOligoMap();
	bool checkLengthCondition(int weigth);
	int checkClassCondition();
	bool addOligosBetweenTwoOligoMap(Edge* edge);
	Graph(Sequence *seq);

private:

};

#endif