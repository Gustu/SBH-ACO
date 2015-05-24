#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Sequence.h"
#include <map>

class Graph
{
public:
	Node *first;
	Sequence *origSeq;

	vector<Edge *> getAdjacencyEdges(Node *node);
	void getPossibbleSequences(Node* node, vector<Oligo*> pSeq, map<string, int> &oligoMap);

	vector< vector<Oligo *> > possibbleSequences;

	void printPossibbleSequences();
	void startSearching();
	void setOligoMap(map<string, int>& oligoMap);
	Graph(Sequence *seq);

private:

};

#endif