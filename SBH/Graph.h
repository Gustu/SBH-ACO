#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Sequence.h"

class Graph
{
public:
	Node *first;
	Sequence *origSeq;

	vector<Edge *> getAdjacencyEdges(Node *node);

	vector< vector<Oligo *> > possibbleSequences;

	void getPossibbleSequences();

	void printPossibbleSequences();

	Graph(Sequence *seq);
	~Graph();

private:

};

#endif